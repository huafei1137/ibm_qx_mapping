OPENQASM 2.0;
include "qelib1.inc";
qreg qr[17];
creg cr[16];
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
x qr[16];
h qr[16];
barrier qr[0],qr[1],qr[2],qr[3],qr[4],qr[5],qr[6],qr[7],qr[8],qr[9],qr[10],qr[11],qr[12],qr[13],qr[14],qr[15],qr[16];
cx qr[0],qr[16];
cx qr[1],qr[16];
cx qr[2],qr[16];
cx qr[3],qr[16];
cx qr[4],qr[16];
cx qr[5],qr[16];
cx qr[6],qr[16];
cx qr[7],qr[16];
cx qr[8],qr[16];
cx qr[9],qr[16];
cx qr[10],qr[16];
cx qr[11],qr[16];
cx qr[12],qr[16];
cx qr[13],qr[16];
cx qr[14],qr[16];
cx qr[15],qr[16];
barrier qr[0],qr[1],qr[2],qr[3],qr[4],qr[5],qr[6],qr[7],qr[8],qr[9],qr[10],qr[11],qr[12],qr[13],qr[14],qr[15],qr[16];
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
