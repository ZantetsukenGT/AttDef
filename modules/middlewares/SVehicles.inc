#include <YSI_Coding\y_hooks>

hook OnScriptInit()
{
	/* Add a Hydra (520) and many others to the game that will respawn 120 seconds after being left 
	with own colors */
	AddStaticVehicleEx(520, 310.0374, 2469.9324, 17.1996, 1.6788, -1, -1, 120);		 // hydra 1 aeropuerto abandonado
	AddStaticVehicleEx(520, 300.0483, 2469.9265, 17.1974, 1.0122, -1, -1, 120);		 // hydra 2 aeropuerto abandonado
	AddStaticVehicleEx(520, 427.6653, 2517.1179, 17.2085, 89.7834, 97, 94, 120);	 // hydra1 lanza
	AddStaticVehicleEx(520, 427.5917, 2504.0916, 17.2076, 90.4866, 78, 111, 120);	 // hydra2 lanza
	AddStaticVehicleEx(520, 427.4420, 2490.8477, 17.2022, 89.0019, 101, 76, 120);	 // hydra3 lanza
	AddStaticVehicleEx(520, 325.0699, 2545.2749, 17.5363, 178.3102, 27, 109, 120);	 // hydra hangar1
	AddStaticVehicleEx(520, 291.2947, 2543.4807, 17.5494, 178.4537, 98, 12, 120);	 // hydra hangar2
	AddStaticVehicleEx(425, 382.7766, 2537.5598, 17.0839, 179.5673, 117, 120, 120);	 // hunterlobb1
	AddStaticVehicleEx(425, 365.1474, 2537.2144, 17.2418, 179.7563, 108, 70, 120);	 // hunterlobb2
	AddStaticVehicleEx(425, 347.4197, 2536.8137, 17.3387, 179.5164, 12, 5, 120);	 // hunterlobb3
	AddStaticVehicleEx(476, 224.7630, 2535.7639, 17.3770, 157.7918, 35, 35, 120);	 // cazafw1901
	AddStaticVehicleEx(476, 210.9377, 2536.0518, 17.3372, 158.7115, 35, 35, 120);	 // cazafw1902
	AddStaticVehicleEx(476, 196.1245, 2536.3997, 17.3341, 158.4676, 35, 35, 120);	 // cazafw1903
	AddStaticVehicleEx(476, 181.4831, 2536.7100, 17.3332, 158.9556, 35, 35, 120);	 // cazafw1904
	AddStaticVehicleEx(476, 167.9568, 2537.4878, 17.3269, 157.9912, 35, 35, 120);	 // cazafw1905
	AddStaticVehicleEx(476, 153.2975, 2537.9229, 17.2976, 158.9733, 35, 35, 120);	 // cazafw1906
	AddStaticVehicleEx(476, 137.7820, 2537.6558, 17.3028, 159.4764, 35, 35, 120);	 // cazafw1907
	AddStaticVehicleEx(476, 122.6575, 2537.5896, 17.3187, 161.3250, 35, 35, 120);	 // cazafw1908
	AddStaticVehicleEx(476, 107.1899, 2537.4385, 17.3160, 162.5948, 35, 35, 120);	 // cazafw1909
	AddStaticVehicleEx(476, 92.2508, 2537.2646, 17.2467, 164.1449, 35, 35, 120);	 // cazafw19010
	AddStaticVehicleEx(476, 76.8649, 2537.3992, 17.1186, 164.1321, 35, 35, 120);	 // cazafw19011
	AddStaticVehicleEx(476, 61.9364, 2537.1023, 17.1270, 163.3188, 35, 35, 120);	 // cazafw19012
	AddStaticVehicleEx(476, 46.8652, 2537.6353, 17.1298, 163.5185, 35, 35, 120);	 // cazafw19013
	AddStaticVehicleEx(476, 31.3967, 2537.8955, 17.1298, 165.4277, 35, 35, 120);	 // cazafw19014
	AddStaticVehicleEx(476, 15.9007, 2538.2771, 17.1177, 165.3586, 35, 35, 120);	 // cazafw19015
	AddStaticVehicleEx(476, -1459.2858, 494.4065, 18.9910, 269.2609, 35, 35, 120);	 // cazaeasterbase4
	AddStaticVehicleEx(476, -1448.2849, 494.4350, 18.9896, 270.0901, 35, 35, 120);	 // cazaeasterbase2
	AddStaticVehicleEx(476, -1448.2634, 507.7130, 18.9558, 270.4851, 35, 35, 120);	 // cazaeasterbase1
	AddStaticVehicleEx(476, -1459.1724, 507.7237, 18.9703, 269.6439, 35, 35, 120);	 // cazaeasterbase3
	AddStaticVehicleEx(476, -1436.9706, 507.6952, 18.9367, 270.7982, 35, 35, 120);	 // cazaeasterbase-1
	AddStaticVehicleEx(476, -1436.8042, 494.5417, 18.9514, 270.5318, 35, 35, 120);	 // cazaeasterbase0
	AddStaticVehicleEx(476, -1271.7804, -627.8026, 14.8549, 331.8907, 35, 35, 120);	 // cazaaero1
	AddStaticVehicleEx(476, -1333.5670, -629.3145, 14.8607, 338.7317, 35, 35, 120);	 // cazaaero2
	AddStaticVehicleEx(476, -1395.3737, -629.2543, 14.8622, 338.5129, 35, 35, 120);	 // cazaaero3
	AddStaticVehicleEx(476, -1457.9967, -629.7150, 14.8607, 331.6295, 35, 35, 120);	 // cazaaero4
	AddStaticVehicleEx(476, -1518.2252, -632.8201, 14.8725, 323.4629, 35, 35, 120);	 // cazaaero5
	AddStaticVehicleEx(476, -1538.8153, -588.6094, 14.8408, 259.1458, 35, 35, 120);	 // cazaaero6
	AddStaticVehicleEx(425, -1324.5654, 444.3454, 7.7557, 330.4325, 107, 3, 120);	 // huntereasterbase1
	AddStaticVehicleEx(425, -1306.2089, 444.2336, 7.7472, 328.0158, 84, 113, 120);	 // huntereasterbase2
	AddStaticVehicleEx(425, -1287.4446, 444.5913, 7.7253, 333.8838, 111, 24, 120);	 // huntereasterbase3
	AddStaticVehicleEx(432, 50.4393, 1168.6017, 18.6739, 181.3071, 104, 3, 120);	 // tankarena1
	AddStaticVehicleEx(432, -15.1626, 1040.3979, 19.6037, 359.3947, 45, 59, 120);	 // tankarena2
	AddStaticVehicleEx(432, -82.7626, 1076.8196, 19.7521, 0.3721, 102, 44, 120);	 // tankarena3
	AddStaticVehicleEx(432, -193.3264, 1000.7891, 19.7826, 359.2780, 103, 104, 120); // tankarena4
	AddStaticVehicleEx(432, -312.8058, 1065.0439, 19.6031, 41.0450, 46, 29, 120);	 // tankarena5
	AddStaticVehicleEx(432, -351.4611, 1157.0168, 19.7498, 212.7353, 64, 87, 120);	 // tankarena6
	AddStaticVehicleEx(432, -226.4156, 1199.9558, 19.5758, 269.7231, 18, 28, 120);	 // tankarena7
	AddStaticVehicleEx(432, -116.8242, 1234.8358, 17.9210, 184.2792, 18, 28, 120);	 // tankarena8
	AddStaticVehicleEx(432, -98.5679, 1153.4685, 19.7522, 268.5540, 18, 28, 120);	 // tankarena9
	AddStaticVehicleEx(520, 289.2515, 2469.7810, 17.1976, 0.1302, 39, 6, 120);		 // hydradelos3

	return 1;
}
