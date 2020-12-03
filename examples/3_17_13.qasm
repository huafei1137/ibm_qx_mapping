OPENQASM 2.0;
include "qelib1.inc";
qreg q[16];
creg c[16];
h q[2]; 
cx q[0], q[5];
cx q[1], q[4];
cx q[2], q[3];
h q[0];

