d = {}
for i in range(int(input())):
    city, num_h = input().split()
    d[city] = [{"time": []}]
    for k in range(int(num_h)):
        timetable, house = input().split()
        timetable = [i for i in range(24) if timetable[i] == "."]
        d[city].append({house: timetable})
        d[city][0]["time"] += timetable



def findCities(arr, time):
    message = "Yes"
    for city in arr:
        for house in d[city][1:]:

            if time in list(house.values())[0]:
                message += " " + str(list(house.keys())[0])
                break
    print(message)



def intersection(arr):
    inter_time = set(d[arr[0]][0]["time"])
    for i in range(1, len(arr)):
        inter_time = inter_time & set(d[arr[i]][0]["time"])
    if not inter_time:
        print("No")
        return
    findCities(arr, list(inter_time)[0])

for i in range(int(input())):
    num_c, *cities_list = input().split()
    intersection(cities_list)