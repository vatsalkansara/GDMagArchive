const int numBasin2Verts = 42;
const int numBasin2Faces = 64;

float basin2Verts[42*3] = {
-0.027583, -0.109007, 0.730612,
0.511510, -0.181521, 0.767407,
1.136707, -0.269613, 0.863075,
1.537066, -0.332166, 0.964769,
2.083714, -0.290545, 1.181710,
-0.018530, -0.040710, 0.679393,
2.255636, -0.109671, 1.174589,
-0.013691, 0.059629, 0.624085,
2.314890, 0.059640, 1.170112,
-0.018530, 0.159967, 0.679393,
2.255636, 0.228951, 1.174589,
-0.027583, 0.228265, 0.730612,
0.511510, 0.300778, 0.767407,
1.136707, 0.388870, 0.863075,
1.537066, 0.451088, 0.964769,
2.083714, 0.409463, 1.181710,
-0.038367, -0.109007, 0.808392,
0.500727, -0.181521, 0.855382,
1.125924, -0.269613, 0.961123,
1.526283, -0.332166, 1.067408,
2.072930, -0.290545, 1.221859,
-0.029313, -0.040710, 0.771543,
0.529043, -0.083855, 0.820213,
1.134977, -0.099638, 0.882843,
1.672339, -0.146749, 0.996523,
2.244853, -0.109671, 1.230389,
-0.024474, 0.059629, 0.731754,
0.546890, 0.059629, 0.771291,
1.139816, 0.059629, 0.827536,
1.721961, 0.059639, 0.945134,
2.304106, 0.059640, 1.241975,
-0.029313, 0.159967, 0.771543,
0.529043, 0.203113, 0.820213,
1.134977, 0.218896, 0.882843,
1.672339, 0.266026, 0.996524,
2.244853, 0.228951, 1.230389,
-0.038367, 0.228265, 0.808393,
0.500727, 0.300778, 0.855382,
1.125924, 0.388870, 0.961123,
1.526283, 0.451088, 1.067408,
2.072930, 0.409463, 1.221859 };


int basin2Indices[64*3] = {
22, 17, 16, 
16, 21, 22, 
23, 18, 17, 
17, 22, 23, 
24, 19, 18, 
18, 23, 24, 
25, 20, 19, 
19, 24, 25, 
27, 22, 21, 
21, 26, 27, 
28, 23, 22, 
22, 27, 28, 
29, 24, 23, 
23, 28, 29, 
30, 25, 24, 
24, 29, 30, 
32, 27, 26, 
26, 31, 32, 
33, 28, 27, 
27, 32, 33, 
34, 29, 28, 
28, 33, 34, 
35, 30, 29, 
29, 34, 35, 
37, 32, 31, 
31, 36, 37, 
38, 33, 32, 
32, 37, 38, 
39, 34, 33, 
33, 38, 39, 
40, 35, 34, 
34, 39, 40, 
17, 1, 0, 
0, 16, 17, 
18, 2, 1, 
1, 17, 18, 
19, 3, 2, 
2, 18, 19, 
20, 4, 3, 
3, 19, 20, 
25, 6, 4, 
4, 20, 25, 
30, 8, 6, 
6, 25, 30, 
35, 10, 8, 
8, 30, 35, 
40, 15, 10, 
10, 35, 40, 
39, 14, 15, 
15, 40, 39, 
38, 13, 14, 
14, 39, 38, 
37, 12, 13, 
13, 38, 37, 
36, 11, 12, 
12, 37, 36, 
31, 9, 11, 
11, 36, 31, 
26, 7, 9, 
9, 31, 26, 
21, 5, 7, 
7, 26, 21, 
16, 0, 5, 
5, 21, 16 };