//Counterfeit coin finding with 299 coins.
//The false coin is 197
OPENQASM 2.0;
include "qelib1.inc";
qreg qr[300];
creg cr[300];
h qr[0];
h qr[1];
h qr[2];
h qr[3];
h qr[4];
h qr[5];
h qr[6];
h qr[7];
h qr[8];
h qr[9];
h qr[10];
h qr[11];
h qr[12];
h qr[13];
h qr[14];
h qr[15];
h qr[16];
h qr[17];
h qr[18];
h qr[19];
h qr[20];
h qr[21];
h qr[22];
h qr[23];
h qr[24];
h qr[25];
h qr[26];
h qr[27];
h qr[28];
h qr[29];
h qr[30];
h qr[31];
h qr[32];
h qr[33];
h qr[34];
h qr[35];
h qr[36];
h qr[37];
h qr[38];
h qr[39];
h qr[40];
h qr[41];
h qr[42];
h qr[43];
h qr[44];
h qr[45];
h qr[46];
h qr[47];
h qr[48];
h qr[49];
h qr[50];
h qr[51];
h qr[52];
h qr[53];
h qr[54];
h qr[55];
h qr[56];
h qr[57];
h qr[58];
h qr[59];
h qr[60];
h qr[61];
h qr[62];
h qr[63];
h qr[64];
h qr[65];
h qr[66];
h qr[67];
h qr[68];
h qr[69];
h qr[70];
h qr[71];
h qr[72];
h qr[73];
h qr[74];
h qr[75];
h qr[76];
h qr[77];
h qr[78];
h qr[79];
h qr[80];
h qr[81];
h qr[82];
h qr[83];
h qr[84];
h qr[85];
h qr[86];
h qr[87];
h qr[88];
h qr[89];
h qr[90];
h qr[91];
h qr[92];
h qr[93];
h qr[94];
h qr[95];
h qr[96];
h qr[97];
h qr[98];
h qr[99];
h qr[100];
h qr[101];
h qr[102];
h qr[103];
h qr[104];
h qr[105];
h qr[106];
h qr[107];
h qr[108];
h qr[109];
h qr[110];
h qr[111];
h qr[112];
h qr[113];
h qr[114];
h qr[115];
h qr[116];
h qr[117];
h qr[118];
h qr[119];
h qr[120];
h qr[121];
h qr[122];
h qr[123];
h qr[124];
h qr[125];
h qr[126];
h qr[127];
h qr[128];
h qr[129];
h qr[130];
h qr[131];
h qr[132];
h qr[133];
h qr[134];
h qr[135];
h qr[136];
h qr[137];
h qr[138];
h qr[139];
h qr[140];
h qr[141];
h qr[142];
h qr[143];
h qr[144];
h qr[145];
h qr[146];
h qr[147];
h qr[148];
h qr[149];
h qr[150];
h qr[151];
h qr[152];
h qr[153];
h qr[154];
h qr[155];
h qr[156];
h qr[157];
h qr[158];
h qr[159];
h qr[160];
h qr[161];
h qr[162];
h qr[163];
h qr[164];
h qr[165];
h qr[166];
h qr[167];
h qr[168];
h qr[169];
h qr[170];
h qr[171];
h qr[172];
h qr[173];
h qr[174];
h qr[175];
h qr[176];
h qr[177];
h qr[178];
h qr[179];
h qr[180];
h qr[181];
h qr[182];
h qr[183];
h qr[184];
h qr[185];
h qr[186];
h qr[187];
h qr[188];
h qr[189];
h qr[190];
h qr[191];
h qr[192];
h qr[193];
h qr[194];
h qr[195];
h qr[196];
h qr[197];
h qr[198];
h qr[199];
h qr[200];
h qr[201];
h qr[202];
h qr[203];
h qr[204];
h qr[205];
h qr[206];
h qr[207];
h qr[208];
h qr[209];
h qr[210];
h qr[211];
h qr[212];
h qr[213];
h qr[214];
h qr[215];
h qr[216];
h qr[217];
h qr[218];
h qr[219];
h qr[220];
h qr[221];
h qr[222];
h qr[223];
h qr[224];
h qr[225];
h qr[226];
h qr[227];
h qr[228];
h qr[229];
h qr[230];
h qr[231];
h qr[232];
h qr[233];
h qr[234];
h qr[235];
h qr[236];
h qr[237];
h qr[238];
h qr[239];
h qr[240];
h qr[241];
h qr[242];
h qr[243];
h qr[244];
h qr[245];
h qr[246];
h qr[247];
h qr[248];
h qr[249];
h qr[250];
h qr[251];
h qr[252];
h qr[253];
h qr[254];
h qr[255];
h qr[256];
h qr[257];
h qr[258];
h qr[259];
h qr[260];
h qr[261];
h qr[262];
h qr[263];
h qr[264];
h qr[265];
h qr[266];
h qr[267];
h qr[268];
h qr[269];
h qr[270];
h qr[271];
h qr[272];
h qr[273];
h qr[274];
h qr[275];
h qr[276];
h qr[277];
h qr[278];
h qr[279];
h qr[280];
h qr[281];
h qr[282];
h qr[283];
h qr[284];
h qr[285];
h qr[286];
h qr[287];
h qr[288];
h qr[289];
h qr[290];
h qr[291];
h qr[292];
h qr[293];
h qr[294];
h qr[295];
h qr[296];
h qr[297];
h qr[298];
cx qr[0],qr[299];
cx qr[1],qr[299];
cx qr[2],qr[299];
cx qr[3],qr[299];
cx qr[4],qr[299];
cx qr[5],qr[299];
cx qr[6],qr[299];
cx qr[7],qr[299];
cx qr[8],qr[299];
cx qr[9],qr[299];
cx qr[10],qr[299];
cx qr[11],qr[299];
cx qr[12],qr[299];
cx qr[13],qr[299];
cx qr[14],qr[299];
cx qr[15],qr[299];
cx qr[16],qr[299];
cx qr[17],qr[299];
cx qr[18],qr[299];
cx qr[19],qr[299];
cx qr[20],qr[299];
cx qr[21],qr[299];
cx qr[22],qr[299];
cx qr[23],qr[299];
cx qr[24],qr[299];
cx qr[25],qr[299];
cx qr[26],qr[299];
cx qr[27],qr[299];
cx qr[28],qr[299];
cx qr[29],qr[299];
cx qr[30],qr[299];
cx qr[31],qr[299];
cx qr[32],qr[299];
cx qr[33],qr[299];
cx qr[34],qr[299];
cx qr[35],qr[299];
cx qr[36],qr[299];
cx qr[37],qr[299];
cx qr[38],qr[299];
cx qr[39],qr[299];
cx qr[40],qr[299];
cx qr[41],qr[299];
cx qr[42],qr[299];
cx qr[43],qr[299];
cx qr[44],qr[299];
cx qr[45],qr[299];
cx qr[46],qr[299];
cx qr[47],qr[299];
cx qr[48],qr[299];
cx qr[49],qr[299];
cx qr[50],qr[299];
cx qr[51],qr[299];
cx qr[52],qr[299];
cx qr[53],qr[299];
cx qr[54],qr[299];
cx qr[55],qr[299];
cx qr[56],qr[299];
cx qr[57],qr[299];
cx qr[58],qr[299];
cx qr[59],qr[299];
cx qr[60],qr[299];
cx qr[61],qr[299];
cx qr[62],qr[299];
cx qr[63],qr[299];
cx qr[64],qr[299];
cx qr[65],qr[299];
cx qr[66],qr[299];
cx qr[67],qr[299];
cx qr[68],qr[299];
cx qr[69],qr[299];
cx qr[70],qr[299];
cx qr[71],qr[299];
cx qr[72],qr[299];
cx qr[73],qr[299];
cx qr[74],qr[299];
cx qr[75],qr[299];
cx qr[76],qr[299];
cx qr[77],qr[299];
cx qr[78],qr[299];
cx qr[79],qr[299];
cx qr[80],qr[299];
cx qr[81],qr[299];
cx qr[82],qr[299];
cx qr[83],qr[299];
cx qr[84],qr[299];
cx qr[85],qr[299];
cx qr[86],qr[299];
cx qr[87],qr[299];
cx qr[88],qr[299];
cx qr[89],qr[299];
cx qr[90],qr[299];
cx qr[91],qr[299];
cx qr[92],qr[299];
cx qr[93],qr[299];
cx qr[94],qr[299];
cx qr[95],qr[299];
cx qr[96],qr[299];
cx qr[97],qr[299];
cx qr[98],qr[299];
cx qr[99],qr[299];
cx qr[100],qr[299];
cx qr[101],qr[299];
cx qr[102],qr[299];
cx qr[103],qr[299];
cx qr[104],qr[299];
cx qr[105],qr[299];
cx qr[106],qr[299];
cx qr[107],qr[299];
cx qr[108],qr[299];
cx qr[109],qr[299];
cx qr[110],qr[299];
cx qr[111],qr[299];
cx qr[112],qr[299];
cx qr[113],qr[299];
cx qr[114],qr[299];
cx qr[115],qr[299];
cx qr[116],qr[299];
cx qr[117],qr[299];
cx qr[118],qr[299];
cx qr[119],qr[299];
cx qr[120],qr[299];
cx qr[121],qr[299];
cx qr[122],qr[299];
cx qr[123],qr[299];
cx qr[124],qr[299];
cx qr[125],qr[299];
cx qr[126],qr[299];
cx qr[127],qr[299];
cx qr[128],qr[299];
cx qr[129],qr[299];
cx qr[130],qr[299];
cx qr[131],qr[299];
cx qr[132],qr[299];
cx qr[133],qr[299];
cx qr[134],qr[299];
cx qr[135],qr[299];
cx qr[136],qr[299];
cx qr[137],qr[299];
cx qr[138],qr[299];
cx qr[139],qr[299];
cx qr[140],qr[299];
cx qr[141],qr[299];
cx qr[142],qr[299];
cx qr[143],qr[299];
cx qr[144],qr[299];
cx qr[145],qr[299];
cx qr[146],qr[299];
cx qr[147],qr[299];
cx qr[148],qr[299];
cx qr[149],qr[299];
cx qr[150],qr[299];
cx qr[151],qr[299];
cx qr[152],qr[299];
cx qr[153],qr[299];
cx qr[154],qr[299];
cx qr[155],qr[299];
cx qr[156],qr[299];
cx qr[157],qr[299];
cx qr[158],qr[299];
cx qr[159],qr[299];
cx qr[160],qr[299];
cx qr[161],qr[299];
cx qr[162],qr[299];
cx qr[163],qr[299];
cx qr[164],qr[299];
cx qr[165],qr[299];
cx qr[166],qr[299];
cx qr[167],qr[299];
cx qr[168],qr[299];
cx qr[169],qr[299];
cx qr[170],qr[299];
cx qr[171],qr[299];
cx qr[172],qr[299];
cx qr[173],qr[299];
cx qr[174],qr[299];
cx qr[175],qr[299];
cx qr[176],qr[299];
cx qr[177],qr[299];
cx qr[178],qr[299];
cx qr[179],qr[299];
cx qr[180],qr[299];
cx qr[181],qr[299];
cx qr[182],qr[299];
cx qr[183],qr[299];
cx qr[184],qr[299];
cx qr[185],qr[299];
cx qr[186],qr[299];
cx qr[187],qr[299];
cx qr[188],qr[299];
cx qr[189],qr[299];
cx qr[190],qr[299];
cx qr[191],qr[299];
cx qr[192],qr[299];
cx qr[193],qr[299];
cx qr[194],qr[299];
cx qr[195],qr[299];
cx qr[196],qr[299];
cx qr[197],qr[299];
cx qr[198],qr[299];
cx qr[199],qr[299];
cx qr[200],qr[299];
cx qr[201],qr[299];
cx qr[202],qr[299];
cx qr[203],qr[299];
cx qr[204],qr[299];
cx qr[205],qr[299];
cx qr[206],qr[299];
cx qr[207],qr[299];
cx qr[208],qr[299];
cx qr[209],qr[299];
cx qr[210],qr[299];
cx qr[211],qr[299];
cx qr[212],qr[299];
cx qr[213],qr[299];
cx qr[214],qr[299];
cx qr[215],qr[299];
cx qr[216],qr[299];
cx qr[217],qr[299];
cx qr[218],qr[299];
cx qr[219],qr[299];
cx qr[220],qr[299];
cx qr[221],qr[299];
cx qr[222],qr[299];
cx qr[223],qr[299];
cx qr[224],qr[299];
cx qr[225],qr[299];
cx qr[226],qr[299];
cx qr[227],qr[299];
cx qr[228],qr[299];
cx qr[229],qr[299];
cx qr[230],qr[299];
cx qr[231],qr[299];
cx qr[232],qr[299];
cx qr[233],qr[299];
cx qr[234],qr[299];
cx qr[235],qr[299];
cx qr[236],qr[299];
cx qr[237],qr[299];
cx qr[238],qr[299];
cx qr[239],qr[299];
cx qr[240],qr[299];
cx qr[241],qr[299];
cx qr[242],qr[299];
cx qr[243],qr[299];
cx qr[244],qr[299];
cx qr[245],qr[299];
cx qr[246],qr[299];
cx qr[247],qr[299];
cx qr[248],qr[299];
cx qr[249],qr[299];
cx qr[250],qr[299];
cx qr[251],qr[299];
cx qr[252],qr[299];
cx qr[253],qr[299];
cx qr[254],qr[299];
cx qr[255],qr[299];
cx qr[256],qr[299];
cx qr[257],qr[299];
cx qr[258],qr[299];
cx qr[259],qr[299];
cx qr[260],qr[299];
cx qr[261],qr[299];
cx qr[262],qr[299];
cx qr[263],qr[299];
cx qr[264],qr[299];
cx qr[265],qr[299];
cx qr[266],qr[299];
cx qr[267],qr[299];
cx qr[268],qr[299];
cx qr[269],qr[299];
cx qr[270],qr[299];
cx qr[271],qr[299];
cx qr[272],qr[299];
cx qr[273],qr[299];
cx qr[274],qr[299];
cx qr[275],qr[299];
cx qr[276],qr[299];
cx qr[277],qr[299];
cx qr[278],qr[299];
cx qr[279],qr[299];
cx qr[280],qr[299];
cx qr[281],qr[299];
cx qr[282],qr[299];
cx qr[283],qr[299];
cx qr[284],qr[299];
cx qr[285],qr[299];
cx qr[286],qr[299];
cx qr[287],qr[299];
cx qr[288],qr[299];
cx qr[289],qr[299];
cx qr[290],qr[299];
cx qr[291],qr[299];
cx qr[292],qr[299];
cx qr[293],qr[299];
cx qr[294],qr[299];
cx qr[295],qr[299];
cx qr[296],qr[299];
cx qr[297],qr[299];
cx qr[298],qr[299];