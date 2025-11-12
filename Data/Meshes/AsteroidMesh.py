import random

head = """{
  "Mesh": {
    "Name": "MeshAsteroid",
    "Vertices": [ \n"""

tail = """    ]
  }
}"""

size = 100

with open("MeshAsteroid.json", 'w') as f:
    f.write(head)
    for _ in range(size):
        rand1 = round(random.uniform(-0.5, 0.5), 3)
        rand2 = round(random.uniform(-0.5, 0.5), 3)
        rand3 = round(random.uniform(0.0, 1.0), 3)
        rand4 = round(random.uniform(0.0, 1.0), 3)
        rand5 = round(random.uniform(0.0, 1.0), 3)
        f.write(f"""      {{ "Position": [ {rand1}, {rand2} ], "Color": [ {rand3}, {rand4}, {rand5}, 1.0 ], "UV": [ 0.0, 0.0 ] }}""")
        if _ < size - 1:
            f.write(",\n")
        else:
            f.write("\n")
    f.write(tail)