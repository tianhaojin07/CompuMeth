import math

PI = 3.1415926535897932

def sin_a(x):
    """Computes sin(x) using the method from 3(a)."""
    # Reduce x to the range [-pi/2, pi/2]
    x_reduced = x % (2 * PI)
    if x_reduced > PI:
        x_reduced -= 2 * PI
    elif x_reduced < -PI:
        x_reduced += 2 * PI
    
    if x_reduced > PI / 2:
        x_reduced = PI - x_reduced
    elif x_reduced < -PI / 2:
        x_reduced = -PI - x_reduced

    if abs(x_reduced) < 1e-8:
        return x_reduced

    if abs(x_reduced) > PI / 6:
        u = x_reduced / 3
        sin_u = sin_a_formula(u)
        return (3 - 4 * sin_u**2) * sin_u
    else: # abs(x_reduced) <= PI / 6
        u = x_reduced
        return sin_a_formula(u)

def sin_a_formula(u):
    """The rational function approximation for sin(u)."""
    u2 = u * u
    u4 = u2 * u2
    u6 = u4 * u2
    numerator = u * (1 - (29593/207636)*u2 + (34911/7613320)*u4 - (479249/11511339840)*u6)
    denominator = 1 + (1671/69212)*u2 + (97/351384)*u4 + (2623/1644477120)*u6
    return numerator / denominator

def sin_b(x):
    """Computes sin(x) using the 4-term Taylor approximation from 3(b)."""
    x2 = x * x
    x3 = x * x2
    x5 = x3 * x2
    x7 = x5 * x2
    return x - x3/math.factorial(3) + x5/math.factorial(5) - x7/math.factorial(7)

x_values = [
    PI/2025, PI/100, PI/10, PI/6, PI/5, PI/4, PI/3
]

print("x\t\tFormula in 3(a)\t\t4-term Taylor (3(b))")
print("-" * 60)

for x in x_values:
    val_a = sin_a(x)
    val_b = sin_b(x)
    # Format to 10 significant figures using "{:.9e}"
    print(f"{x/PI:.4f}*pi\t\t{val_a:.9e}\t{val_b:.9e}")