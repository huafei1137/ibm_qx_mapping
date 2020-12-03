OPENQASM 2.0;
include "qelib1.inc";
qreg q[18];
creg c[18];
h q[0];
u1(0.785398163397448) q[1];
cx q[1],q[0];
u1(-0.785398163397448) q[0];
cx q[1],q[0];
u1(0.785398163397448) q[0];
h q[1];
u1(0.392699081698724) q[2];
cx q[2],q[0];
u1(-0.392699081698724) q[0];
cx q[2],q[0];
u1(0.392699081698724) q[0];
u1(0.785398163397448) q[2];
cx q[2],q[1];
u1(-0.785398163397448) q[1];
cx q[2],q[1];
u1(0.785398163397448) q[1];
h q[2];
u1(0.196349540849362) q[3];
cx q[3],q[0];
u1(-0.196349540849362) q[0];
cx q[3],q[0];
u1(0.196349540849362) q[0];
u1(0.392699081698724) q[3];
cx q[3],q[1];
u1(-0.392699081698724) q[1];
cx q[3],q[1];
u1(0.392699081698724) q[1];
u1(0.785398163397448) q[3];
cx q[3],q[2];
u1(-0.785398163397448) q[2];
cx q[3],q[2];
u1(0.785398163397448) q[2];
h q[3];
u1(0.0981747704246810) q[4];
cx q[4],q[0];
u1(-0.0981747704246810) q[0];
cx q[4],q[0];
u1(0.0981747704246810) q[0];
u1(0.196349540849362) q[4];
cx q[4],q[1];
u1(-0.196349540849362) q[1];
cx q[4],q[1];
u1(0.196349540849362) q[1];
u1(0.392699081698724) q[4];
cx q[4],q[2];
u1(-0.392699081698724) q[2];
cx q[4],q[2];
u1(0.392699081698724) q[2];
u1(0.785398163397448) q[4];
cx q[4],q[3];
u1(-0.785398163397448) q[3];
cx q[4],q[3];
u1(0.785398163397448) q[3];
h q[4];
u1(0.0490873852123405) q[5];
cx q[5],q[0];
u1(-0.0490873852123405) q[0];
cx q[5],q[0];
u1(0.0490873852123405) q[0];
u1(0.0981747704246810) q[5];
cx q[5],q[1];
u1(-0.0981747704246810) q[1];
cx q[5],q[1];
u1(0.0981747704246810) q[1];
u1(0.196349540849362) q[5];
cx q[5],q[2];
u1(-0.196349540849362) q[2];
cx q[5],q[2];
u1(0.196349540849362) q[2];
u1(0.392699081698724) q[5];
cx q[5],q[3];
u1(-0.392699081698724) q[3];
cx q[5],q[3];
u1(0.392699081698724) q[3];
u1(0.785398163397448) q[5];
cx q[5],q[4];
u1(-0.785398163397448) q[4];
cx q[5],q[4];
u1(0.785398163397448) q[4];
h q[5];
u1(0.0245436926061703) q[6];
cx q[6],q[0];
u1(-0.0245436926061703) q[0];
cx q[6],q[0];
u1(0.0245436926061703) q[0];
u1(0.0490873852123405) q[6];
cx q[6],q[1];
u1(-0.0490873852123405) q[1];
cx q[6],q[1];
u1(0.0490873852123405) q[1];
u1(0.0981747704246810) q[6];
cx q[6],q[2];
u1(-0.0981747704246810) q[2];
cx q[6],q[2];
u1(0.0981747704246810) q[2];
u1(0.196349540849362) q[6];
cx q[6],q[3];
u1(-0.196349540849362) q[3];
cx q[6],q[3];
u1(0.196349540849362) q[3];
u1(0.392699081698724) q[6];
cx q[6],q[4];
u1(-0.392699081698724) q[4];
cx q[6],q[4];
u1(0.392699081698724) q[4];
u1(0.785398163397448) q[6];
cx q[6],q[5];
u1(-0.785398163397448) q[5];
cx q[6],q[5];
u1(0.785398163397448) q[5];
h q[6];
u1(0.0122718463030851) q[7];
cx q[7],q[0];
u1(-0.0122718463030851) q[0];
cx q[7],q[0];
u1(0.0122718463030851) q[0];
u1(0.0245436926061703) q[7];
cx q[7],q[1];
u1(-0.0245436926061703) q[1];
cx q[7],q[1];
u1(0.0245436926061703) q[1];
u1(0.0490873852123405) q[7];
cx q[7],q[2];
u1(-0.0490873852123405) q[2];
cx q[7],q[2];
u1(0.0490873852123405) q[2];
u1(0.0981747704246810) q[7];
cx q[7],q[3];
u1(-0.0981747704246810) q[3];
cx q[7],q[3];
u1(0.0981747704246810) q[3];
u1(0.196349540849362) q[7];
cx q[7],q[4];
u1(-0.196349540849362) q[4];
cx q[7],q[4];
u1(0.196349540849362) q[4];
u1(0.392699081698724) q[7];
cx q[7],q[5];
u1(-0.392699081698724) q[5];
cx q[7],q[5];
u1(0.392699081698724) q[5];
u1(0.785398163397448) q[7];
cx q[7],q[6];
u1(-0.785398163397448) q[6];
cx q[7],q[6];
u1(0.785398163397448) q[6];
h q[7];
u1(0.00613592315154256) q[8];
cx q[8],q[0];
u1(-0.00613592315154256) q[0];
cx q[8],q[0];
u1(0.00613592315154256) q[0];
u1(0.0122718463030851) q[8];
cx q[8],q[1];
u1(-0.0122718463030851) q[1];
cx q[8],q[1];
u1(0.0122718463030851) q[1];
u1(0.0245436926061703) q[8];
cx q[8],q[2];
u1(-0.0245436926061703) q[2];
cx q[8],q[2];
u1(0.0245436926061703) q[2];
u1(0.0490873852123405) q[8];
cx q[8],q[3];
u1(-0.0490873852123405) q[3];
cx q[8],q[3];
u1(0.0490873852123405) q[3];
u1(0.0981747704246810) q[8];
cx q[8],q[4];
u1(-0.0981747704246810) q[4];
cx q[8],q[4];
u1(0.0981747704246810) q[4];
u1(0.196349540849362) q[8];
cx q[8],q[5];
u1(-0.196349540849362) q[5];
cx q[8],q[5];
u1(0.196349540849362) q[5];
u1(0.392699081698724) q[8];
cx q[8],q[6];
u1(-0.392699081698724) q[6];
cx q[8],q[6];
u1(0.392699081698724) q[6];
u1(0.785398163397448) q[8];
cx q[8],q[7];
u1(-0.785398163397448) q[7];
cx q[8],q[7];
u1(0.785398163397448) q[7];
h q[8];
u1(0.00306796157577128) q[9];
cx q[9],q[0];
u1(-0.00306796157577128) q[0];
cx q[9],q[0];
u1(0.00306796157577128) q[0];
u1(0.00613592315154256) q[9];
cx q[9],q[1];
u1(-0.00613592315154256) q[1];
cx q[9],q[1];
u1(0.00613592315154256) q[1];
u1(0.0122718463030851) q[9];
cx q[9],q[2];
u1(-0.0122718463030851) q[2];
cx q[9],q[2];
u1(0.0122718463030851) q[2];
u1(0.0245436926061703) q[9];
cx q[9],q[3];
u1(-0.0245436926061703) q[3];
cx q[9],q[3];
u1(0.0245436926061703) q[3];
u1(0.0490873852123405) q[9];
cx q[9],q[4];
u1(-0.0490873852123405) q[4];
cx q[9],q[4];
u1(0.0490873852123405) q[4];
u1(0.0981747704246810) q[9];
cx q[9],q[5];
u1(-0.0981747704246810) q[5];
cx q[9],q[5];
u1(0.0981747704246810) q[5];
u1(0.196349540849362) q[9];
cx q[9],q[6];
u1(-0.196349540849362) q[6];
cx q[9],q[6];
u1(0.196349540849362) q[6];
u1(0.392699081698724) q[9];
cx q[9],q[7];
u1(-0.392699081698724) q[7];
cx q[9],q[7];
u1(0.392699081698724) q[7];
u1(0.785398163397448) q[9];
cx q[9],q[8];
u1(-0.785398163397448) q[8];
cx q[9],q[8];
u1(0.785398163397448) q[8];
h q[9];
u1(0.00153398078788564) q[10];
cx q[10],q[0];
u1(-0.00153398078788564) q[0];
cx q[10],q[0];
u1(0.00153398078788564) q[0];
u1(0.00306796157577128) q[10];
cx q[10],q[1];
u1(-0.00306796157577128) q[1];
cx q[10],q[1];
u1(0.00306796157577128) q[1];
u1(0.00613592315154256) q[10];
cx q[10],q[2];
u1(-0.00613592315154256) q[2];
cx q[10],q[2];
u1(0.00613592315154256) q[2];
u1(0.0122718463030851) q[10];
cx q[10],q[3];
u1(-0.0122718463030851) q[3];
cx q[10],q[3];
u1(0.0122718463030851) q[3];
u1(0.0245436926061703) q[10];
cx q[10],q[4];
u1(-0.0245436926061703) q[4];
cx q[10],q[4];
u1(0.0245436926061703) q[4];
u1(0.0490873852123405) q[10];
cx q[10],q[5];
u1(-0.0490873852123405) q[5];
cx q[10],q[5];
u1(0.0490873852123405) q[5];
u1(0.0981747704246810) q[10];
cx q[10],q[6];
u1(-0.0981747704246810) q[6];
cx q[10],q[6];
u1(0.0981747704246810) q[6];
u1(0.196349540849362) q[10];
cx q[10],q[7];
u1(-0.196349540849362) q[7];
cx q[10],q[7];
u1(0.196349540849362) q[7];
u1(0.392699081698724) q[10];
cx q[10],q[8];
u1(-0.392699081698724) q[8];
cx q[10],q[8];
u1(0.392699081698724) q[8];
u1(0.785398163397448) q[10];
cx q[10],q[9];
u1(-0.785398163397448) q[9];
cx q[10],q[9];
u1(0.785398163397448) q[9];
h q[10];
u1(0.000766990393942821) q[11];
cx q[11],q[0];
u1(-0.000766990393942821) q[0];
cx q[11],q[0];
u1(0.000766990393942821) q[0];
u1(0.00153398078788564) q[11];
cx q[11],q[1];
u1(-0.00153398078788564) q[1];
cx q[11],q[1];
u1(0.00153398078788564) q[1];
u1(0.00306796157577128) q[11];
cx q[11],q[2];
u1(-0.00306796157577128) q[2];
cx q[11],q[2];
u1(0.00306796157577128) q[2];
u1(0.00613592315154256) q[11];
cx q[11],q[3];
u1(-0.00613592315154256) q[3];
cx q[11],q[3];
u1(0.00613592315154256) q[3];
u1(0.0122718463030851) q[11];
cx q[11],q[4];
u1(-0.0122718463030851) q[4];
cx q[11],q[4];
u1(0.0122718463030851) q[4];
u1(0.0245436926061703) q[11];
cx q[11],q[5];
u1(-0.0245436926061703) q[5];
cx q[11],q[5];
u1(0.0245436926061703) q[5];
u1(0.0490873852123405) q[11];
cx q[11],q[6];
u1(-0.0490873852123405) q[6];
cx q[11],q[6];
u1(0.0490873852123405) q[6];
u1(0.0981747704246810) q[11];
cx q[11],q[7];
u1(-0.0981747704246810) q[7];
cx q[11],q[7];
u1(0.0981747704246810) q[7];
u1(0.196349540849362) q[11];
cx q[11],q[8];
u1(-0.196349540849362) q[8];
cx q[11],q[8];
u1(0.196349540849362) q[8];
u1(0.392699081698724) q[11];
cx q[11],q[9];
u1(-0.392699081698724) q[9];
cx q[11],q[9];
u1(0.392699081698724) q[9];
u1(0.785398163397448) q[11];
cx q[11],q[10];
u1(-0.785398163397448) q[10];
cx q[11],q[10];
u1(0.785398163397448) q[10];
h q[11];
u1(0.000383495196971410) q[12];
cx q[12],q[0];
u1(-0.000383495196971410) q[0];
cx q[12],q[0];
u1(0.000383495196971410) q[0];
u1(0.000766990393942821) q[12];
cx q[12],q[1];
u1(-0.000766990393942821) q[1];
cx q[12],q[1];
u1(0.000766990393942821) q[1];
u1(0.00153398078788564) q[12];
cx q[12],q[2];
u1(-0.00153398078788564) q[2];
cx q[12],q[2];
u1(0.00153398078788564) q[2];
u1(0.00306796157577128) q[12];
cx q[12],q[3];
u1(-0.00306796157577128) q[3];
cx q[12],q[3];
u1(0.00306796157577128) q[3];
u1(0.00613592315154256) q[12];
cx q[12],q[4];
u1(-0.00613592315154256) q[4];
cx q[12],q[4];
u1(0.00613592315154256) q[4];
u1(0.0122718463030851) q[12];
cx q[12],q[5];
u1(-0.0122718463030851) q[5];
cx q[12],q[5];
u1(0.0122718463030851) q[5];
u1(0.0245436926061703) q[12];
cx q[12],q[6];
u1(-0.0245436926061703) q[6];
cx q[12],q[6];
u1(0.0245436926061703) q[6];
u1(0.0490873852123405) q[12];
cx q[12],q[7];
u1(-0.0490873852123405) q[7];
cx q[12],q[7];
u1(0.0490873852123405) q[7];
u1(0.0981747704246810) q[12];
cx q[12],q[8];
u1(-0.0981747704246810) q[8];
cx q[12],q[8];
u1(0.0981747704246810) q[8];
u1(0.196349540849362) q[12];
cx q[12],q[9];
u1(-0.196349540849362) q[9];
cx q[12],q[9];
u1(0.196349540849362) q[9];
u1(0.392699081698724) q[12];
cx q[12],q[10];
u1(-0.392699081698724) q[10];
cx q[12],q[10];
u1(0.392699081698724) q[10];
u1(0.785398163397448) q[12];
cx q[12],q[11];
u1(-0.785398163397448) q[11];
cx q[12],q[11];
u1(0.785398163397448) q[11];
h q[12];
u1(0.000191747598485705) q[13];
cx q[13],q[0];
u1(-0.000191747598485705) q[0];
cx q[13],q[0];
u1(0.000191747598485705) q[0];
u1(0.000383495196971410) q[13];
cx q[13],q[1];
u1(-0.000383495196971410) q[1];
cx q[13],q[1];
u1(0.000383495196971410) q[1];
u1(0.000766990393942821) q[13];
cx q[13],q[2];
u1(-0.000766990393942821) q[2];
cx q[13],q[2];
u1(0.000766990393942821) q[2];
u1(0.00153398078788564) q[13];
cx q[13],q[3];
u1(-0.00153398078788564) q[3];
cx q[13],q[3];
u1(0.00153398078788564) q[3];
u1(0.00306796157577128) q[13];
cx q[13],q[4];
u1(-0.00306796157577128) q[4];
cx q[13],q[4];
u1(0.00306796157577128) q[4];
u1(0.00613592315154256) q[13];
cx q[13],q[5];
u1(-0.00613592315154256) q[5];
cx q[13],q[5];
u1(0.00613592315154256) q[5];
u1(0.0122718463030851) q[13];
cx q[13],q[6];
u1(-0.0122718463030851) q[6];
cx q[13],q[6];
u1(0.0122718463030851) q[6];
u1(0.0245436926061703) q[13];
cx q[13],q[7];
u1(-0.0245436926061703) q[7];
cx q[13],q[7];
u1(0.0245436926061703) q[7];
u1(0.0490873852123405) q[13];
cx q[13],q[8];
u1(-0.0490873852123405) q[8];
cx q[13],q[8];
u1(0.0490873852123405) q[8];
u1(0.0981747704246810) q[13];
cx q[13],q[9];
u1(-0.0981747704246810) q[9];
cx q[13],q[9];
u1(0.0981747704246810) q[9];
u1(0.196349540849362) q[13];
cx q[13],q[10];
u1(-0.196349540849362) q[10];
cx q[13],q[10];
u1(0.196349540849362) q[10];
u1(0.392699081698724) q[13];
cx q[13],q[11];
u1(-0.392699081698724) q[11];
cx q[13],q[11];
u1(0.392699081698724) q[11];
u1(0.785398163397448) q[13];
cx q[13],q[12];
u1(-0.785398163397448) q[12];
cx q[13],q[12];
u1(0.785398163397448) q[12];
h q[13];
u1(9.58737992428526e-5) q[14];
cx q[14],q[0];
u1(-9.58737992428526e-5) q[0];
cx q[14],q[0];
u1(9.58737992428526e-5) q[0];
u1(0.000191747598485705) q[14];
cx q[14],q[1];
u1(-0.000191747598485705) q[1];
cx q[14],q[1];
u1(0.000191747598485705) q[1];
u1(0.000383495196971410) q[14];
cx q[14],q[2];
u1(-0.000383495196971410) q[2];
cx q[14],q[2];
u1(0.000383495196971410) q[2];
u1(0.000766990393942821) q[14];
cx q[14],q[3];
u1(-0.000766990393942821) q[3];
cx q[14],q[3];
u1(0.000766990393942821) q[3];
u1(0.00153398078788564) q[14];
cx q[14],q[4];
u1(-0.00153398078788564) q[4];
cx q[14],q[4];
u1(0.00153398078788564) q[4];
u1(0.00306796157577128) q[14];
cx q[14],q[5];
u1(-0.00306796157577128) q[5];
cx q[14],q[5];
u1(0.00306796157577128) q[5];
u1(0.00613592315154256) q[14];
cx q[14],q[6];
u1(-0.00613592315154256) q[6];
cx q[14],q[6];
u1(0.00613592315154256) q[6];
u1(0.0122718463030851) q[14];
cx q[14],q[7];
u1(-0.0122718463030851) q[7];
cx q[14],q[7];
u1(0.0122718463030851) q[7];
u1(0.0245436926061703) q[14];
cx q[14],q[8];
u1(-0.0245436926061703) q[8];
cx q[14],q[8];
u1(0.0245436926061703) q[8];
u1(0.0490873852123405) q[14];
cx q[14],q[9];
u1(-0.0490873852123405) q[9];
cx q[14],q[9];
u1(0.0490873852123405) q[9];
u1(0.0981747704246810) q[14];
cx q[14],q[10];
u1(-0.0981747704246810) q[10];
cx q[14],q[10];
u1(0.0981747704246810) q[10];
u1(0.196349540849362) q[14];
cx q[14],q[11];
u1(-0.196349540849362) q[11];
cx q[14],q[11];
u1(0.196349540849362) q[11];
u1(0.392699081698724) q[14];
cx q[14],q[12];
u1(-0.392699081698724) q[12];
cx q[14],q[12];
u1(0.392699081698724) q[12];
u1(0.785398163397448) q[14];
cx q[14],q[13];
u1(-0.785398163397448) q[13];
cx q[14],q[13];
u1(0.785398163397448) q[13];
h q[14];
u1(4.79368996214263e-5) q[15];
cx q[15],q[0];
u1(-4.79368996214263e-5) q[0];
cx q[15],q[0];
u1(4.79368996214263e-5) q[0];
u1(9.58737992428526e-5) q[15];
cx q[15],q[1];
u1(-9.58737992428526e-5) q[1];
cx q[15],q[1];
u1(9.58737992428526e-5) q[1];
u1(0.000191747598485705) q[15];
cx q[15],q[2];
u1(-0.000191747598485705) q[2];
cx q[15],q[2];
u1(0.000191747598485705) q[2];
u1(0.000383495196971410) q[15];
cx q[15],q[3];
u1(-0.000383495196971410) q[3];
cx q[15],q[3];
u1(0.000383495196971410) q[3];
u1(0.000766990393942821) q[15];
cx q[15],q[4];
u1(-0.000766990393942821) q[4];
cx q[15],q[4];
u1(0.000766990393942821) q[4];
u1(0.00153398078788564) q[15];
cx q[15],q[5];
u1(-0.00153398078788564) q[5];
cx q[15],q[5];
u1(0.00153398078788564) q[5];
u1(0.00306796157577128) q[15];
cx q[15],q[6];
u1(-0.00306796157577128) q[6];
cx q[15],q[6];
u1(0.00306796157577128) q[6];
u1(0.00613592315154256) q[15];
cx q[15],q[7];
u1(-0.00613592315154256) q[7];
cx q[15],q[7];
u1(0.00613592315154256) q[7];
u1(0.0122718463030851) q[15];
cx q[15],q[8];
u1(-0.0122718463030851) q[8];
cx q[15],q[8];
u1(0.0122718463030851) q[8];
u1(0.0245436926061703) q[15];
cx q[15],q[9];
u1(-0.0245436926061703) q[9];
cx q[15],q[9];
u1(0.0245436926061703) q[9];
u1(0.0490873852123405) q[15];
cx q[15],q[10];
u1(-0.0490873852123405) q[10];
cx q[15],q[10];
u1(0.0490873852123405) q[10];
u1(0.0981747704246810) q[15];
cx q[15],q[11];
u1(-0.0981747704246810) q[11];
cx q[15],q[11];
u1(0.0981747704246810) q[11];
u1(0.196349540849362) q[15];
cx q[15],q[12];
u1(-0.196349540849362) q[12];
cx q[15],q[12];
u1(0.196349540849362) q[12];
u1(0.392699081698724) q[15];
cx q[15],q[13];
u1(-0.392699081698724) q[13];
cx q[15],q[13];
u1(0.392699081698724) q[13];
u1(0.785398163397448) q[15];
cx q[15],q[14];
u1(-0.785398163397448) q[14];
cx q[15],q[14];
u1(0.785398163397448) q[14];
h q[15];
u1(2.39684498107131e-5) q[16];
cx q[16],q[0];
u1(-2.39684498107131e-5) q[0];
cx q[16],q[0];
u1(2.39684498107131e-5) q[0];
u1(4.79368996214263e-5) q[16];
cx q[16],q[1];
u1(-4.79368996214263e-5) q[1];
cx q[16],q[1];
u1(4.79368996214263e-5) q[1];
u1(9.58737992428526e-5) q[16];
cx q[16],q[2];
u1(-9.58737992428526e-5) q[2];
cx q[16],q[2];
u1(9.58737992428526e-5) q[2];
u1(0.000191747598485705) q[16];
cx q[16],q[3];
u1(-0.000191747598485705) q[3];
cx q[16],q[3];
u1(0.000191747598485705) q[3];
u1(0.000383495196971410) q[16];
cx q[16],q[4];
u1(-0.000383495196971410) q[4];
cx q[16],q[4];
u1(0.000383495196971410) q[4];
u1(0.000766990393942821) q[16];
cx q[16],q[5];
u1(-0.000766990393942821) q[5];
cx q[16],q[5];
u1(0.000766990393942821) q[5];
u1(0.00153398078788564) q[16];
cx q[16],q[6];
u1(-0.00153398078788564) q[6];
cx q[16],q[6];
u1(0.00153398078788564) q[6];
u1(0.00306796157577128) q[16];
cx q[16],q[7];
u1(-0.00306796157577128) q[7];
cx q[16],q[7];
u1(0.00306796157577128) q[7];
u1(0.00613592315154256) q[16];
cx q[16],q[8];
u1(-0.00613592315154256) q[8];
cx q[16],q[8];
u1(0.00613592315154256) q[8];
u1(0.0122718463030851) q[16];
cx q[16],q[9];
u1(-0.0122718463030851) q[9];
cx q[16],q[9];
u1(0.0122718463030851) q[9];
u1(0.0245436926061703) q[16];
cx q[16],q[10];
u1(-0.0245436926061703) q[10];
cx q[16],q[10];
u1(0.0245436926061703) q[10];
u1(0.0490873852123405) q[16];
cx q[16],q[11];
u1(-0.0490873852123405) q[11];
cx q[16],q[11];
u1(0.0490873852123405) q[11];
u1(0.0981747704246810) q[16];
cx q[16],q[12];
u1(-0.0981747704246810) q[12];
cx q[16],q[12];
u1(0.0981747704246810) q[12];
u1(0.196349540849362) q[16];
cx q[16],q[13];
u1(-0.196349540849362) q[13];
cx q[16],q[13];
u1(0.196349540849362) q[13];
u1(0.392699081698724) q[16];
cx q[16],q[14];
u1(-0.392699081698724) q[14];
cx q[16],q[14];
u1(0.392699081698724) q[14];
u1(0.785398163397448) q[16];
cx q[16],q[15];
u1(-0.785398163397448) q[15];
cx q[16],q[15];
u1(0.785398163397448) q[15];
h q[16];
u1(1.19842249053566e-5) q[17];
cx q[17],q[0];
u1(-1.19842249053566e-5) q[0];
cx q[17],q[0];
u1(1.19842249053566e-5) q[0];
u1(2.39684498107131e-5) q[17];
cx q[17],q[1];
u1(-2.39684498107131e-5) q[1];
cx q[17],q[1];
u1(2.39684498107131e-5) q[1];
u1(4.79368996214263e-5) q[17];
cx q[17],q[2];
u1(-4.79368996214263e-5) q[2];
cx q[17],q[2];
u1(4.79368996214263e-5) q[2];
u1(9.58737992428526e-5) q[17];
cx q[17],q[3];
u1(-9.58737992428526e-5) q[3];
cx q[17],q[3];
u1(9.58737992428526e-5) q[3];
u1(0.000191747598485705) q[17];
cx q[17],q[4];
u1(-0.000191747598485705) q[4];
cx q[17],q[4];
u1(0.000191747598485705) q[4];
u1(0.000383495196971410) q[17];
cx q[17],q[5];
u1(-0.000383495196971410) q[5];
cx q[17],q[5];
u1(0.000383495196971410) q[5];
u1(0.000766990393942821) q[17];
cx q[17],q[6];
u1(-0.000766990393942821) q[6];
cx q[17],q[6];
u1(0.000766990393942821) q[6];
u1(0.00153398078788564) q[17];
cx q[17],q[7];
u1(-0.00153398078788564) q[7];
cx q[17],q[7];
u1(0.00153398078788564) q[7];
u1(0.00306796157577128) q[17];
cx q[17],q[8];
u1(-0.00306796157577128) q[8];
cx q[17],q[8];
u1(0.00306796157577128) q[8];
u1(0.00613592315154256) q[17];
cx q[17],q[9];
u1(-0.00613592315154256) q[9];
cx q[17],q[9];
u1(0.00613592315154256) q[9];
u1(0.0122718463030851) q[17];
cx q[17],q[10];
u1(-0.0122718463030851) q[10];
cx q[17],q[10];
u1(0.0122718463030851) q[10];
u1(0.0245436926061703) q[17];
cx q[17],q[11];
u1(-0.0245436926061703) q[11];
cx q[17],q[11];
u1(0.0245436926061703) q[11];
u1(0.0490873852123405) q[17];
cx q[17],q[12];
u1(-0.0490873852123405) q[12];
cx q[17],q[12];
u1(0.0490873852123405) q[12];
u1(0.0981747704246810) q[17];
cx q[17],q[13];
u1(-0.0981747704246810) q[13];
cx q[17],q[13];
u1(0.0981747704246810) q[13];
u1(0.196349540849362) q[17];
cx q[17],q[14];
u1(-0.196349540849362) q[14];
cx q[17],q[14];
u1(0.196349540849362) q[14];
u1(0.392699081698724) q[17];
cx q[17],q[15];
u1(-0.392699081698724) q[15];
cx q[17],q[15];
u1(0.392699081698724) q[15];
u1(0.785398163397448) q[17];
cx q[17],q[16];
u1(-0.785398163397448) q[16];
cx q[17],q[16];
u1(0.785398163397448) q[16];
h q[17];
barrier q[0],q[1],q[2],q[3],q[4],q[5],q[6],q[7],q[8],q[9],q[10],q[11],q[12],q[13],q[14],q[15],q[16],q[17];
