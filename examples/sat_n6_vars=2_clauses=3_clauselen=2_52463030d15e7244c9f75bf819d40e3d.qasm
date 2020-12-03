include "qelib1.inc";
qreg v[3];
qreg c[3];
qreg a[1];
creg m[2];
h v[1];
h v[2];

cx v[2], c[0];
cx v[1], c[1];
ccx v[1], v[2], c[2];
ccx c[0], c[1], a[0];
ccx c[2], a[0], v[0];
ccx c[0], c[1], a[0];
ccx v[1], v[2], c[2];
cx v[1], c[1];
cx v[2], c[0];


h v[1];
h v[2];
h v[0];
ccx v[1], v[2], v[0];
h v[0];
h v[0];
h v[1];
h v[2];

