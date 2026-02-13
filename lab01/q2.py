import math

data = [
    4042.045051380452,
    0.000531415926535,
    -2759471.276702747,
    0.0000557052996742895,
    2755463.874010974,
    -0.000031415926535,
    -34.64291531256604
]

# (a) Sequential order
sum_a = 0.0
for x in data:
    sum_a += x

# (b) Reverse order
sum_b = 0.0
for x in reversed(data):
    sum_b += x

# (c) Descending order of absolute values
data_c = sorted(data, key=abs, reverse=True)
sum_c = 0.0
for x in data_c:
    sum_c += x

# (d) Ascending order of absolute values
data_d = sorted(data, key=abs)
sum_d = 0.0
for x in data_d:
    sum_d += x

# "Exact" value using math.fsum
exact_sum = math.fsum(data)

print("Method\t\tSum")
print("-" * 40)
print(f"(a) Sequential\t{sum_a:.9e}")
print(f"(b) Reverse\t\t{sum_b:.9e}")
print(f"(c) Descending Abs\t{sum_c:.9e}")
print(f"(d) Ascending Abs\t{sum_d:.9e}")
print(f"Exact (math.fsum)\t{exact_sum:.9e}")