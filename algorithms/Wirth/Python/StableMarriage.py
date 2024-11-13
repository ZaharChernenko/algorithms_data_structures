from typing import Generator


class StableMarriage:
    def __init__(self, man_pref: list[list[int]], woman_pref: list[list[int]]):
        self._n_couples: int = len(man_pref)
        self._man_pref = man_pref
        self._man_woman2rank: list[list[int]] = [[0] * self._n_couples for _ in range(self._n_couples)]
        for man in range(self._n_couples):
            for rank, woman in enumerate(man_pref[man]):
                self._man_woman2rank[man][woman] = rank
        # woman_man2rank[i][j] - рейтинг j мужчины по мнению i женщины, чем меньше, тем лучше
        self._woman_man2rank: list[list[int]] = [[0] * self._n_couples for _ in range(self._n_couples)]
        for woman in range(self._n_couples):
            for rank, man in enumerate(woman_pref[woman]):
                self._woman_man2rank[woman][man] = rank

        self._woman2man: list[int | None]
        self._man2woman: list[int | None]

    def isStable(self, man: int, woman: int) -> bool:
        """
        Проверяем стабильность на текущий момент, т.е. везде только занятые кандидаты
        """
        # другая пара для мужчины
        for new_woman in self._man_pref[man]:
            # далее бессмысленно идти
            if woman == new_woman:
                break
            if (
                self._woman2man[new_woman] is not None
                and self._woman_man2rank[new_woman][self._woman2man[new_woman]] > self._woman_man2rank[new_woman][man]
            ):
                return False

        # другая пара для женщины ищем только по занятым мужчинам, т.е. походу рекурсии первые man мужчин уже заняты
        for new_man in range(man):
            if (
                self._woman_man2rank[woman][man] > self._woman_man2rank[woman][new_man]
                and self._man_woman2rank[new_man][self._man2woman[new_man]] > self._man_woman2rank[new_man][woman]
            ):
                return False

        return True

    def _genMarriages(self, cur_man: int) -> Generator[list[int], None, None]:
        if cur_man == self._n_couples:
            yield list(self._man2woman)
            return

        for woman in self._man_pref[cur_man]:
            if self._woman2man[woman] is None and self.isStable(cur_man, woman):
                self._man2woman[cur_man] = woman
                self._woman2man[woman] = cur_man
                yield from self._genMarriages(cur_man + 1)
                self._man2woman[cur_man] = None
                self._woman2man[woman] = None

    def __iter__(self) -> Generator[list[int], None, None]:
        self._man2woman = [None] * self._n_couples
        # количество незанятых женщин
        self._woman2man = [None] * self._n_couples
        return self._genMarriages(0)


man_pref = [
    [7, 2, 6, 5, 1, 3, 8, 4],
    [4, 3, 2, 6, 8, 1, 7, 5],
    [3, 2, 4, 1, 8, 5, 7, 6],
    [3, 8, 4, 2, 5, 6, 7, 1],
    [8, 3, 4, 5, 6, 1, 7, 2],
    [8, 7, 5, 2, 4, 3, 1, 6],
    [2, 4, 6, 3, 1, 7, 5, 8],
    [6, 1, 4, 2, 7, 5, 3, 8],
]

woman_pref = [
    [4, 6, 2, 5, 8, 1, 3, 7],
    [8, 5, 3, 1, 6, 7, 4, 2],
    [6, 8, 1, 2, 3, 4, 7, 5],
    [3, 2, 4, 7, 6, 8, 5, 1],
    [6, 3, 1, 4, 5, 7, 2, 8],
    [2, 1, 3, 8, 7, 4, 6, 5],
    [3, 5, 7, 2, 4, 1, 8, 6],
    [7, 2, 8, 4, 5, 6, 3, 1],
]


for i in range(len(man_pref)):
    for j in range(len(man_pref)):
        man_pref[i][j] -= 1
        woman_pref[i][j] -= 1


s = StableMarriage(man_pref, woman_pref)

for sol in s:
    print(sol)
