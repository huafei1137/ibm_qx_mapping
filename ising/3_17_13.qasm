OPENQASM 2.0;
include "qelib1.inc";
qreg q[16];
creg c[16];
 
cx q[0], q[5];
cx q[0], q[5];
cx q[0], q[5];
cx q[0], q[5];
cx q[1], q[4];
cx q[2], q[3];
cx q[6], q[7];
cx q[8], q[9];
cx q[10], q[11];
cx q[11], q[14];
cx q[12], q[13];
h q[0];

