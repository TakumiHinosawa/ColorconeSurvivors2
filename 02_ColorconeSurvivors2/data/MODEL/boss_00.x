xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 158;
 17.34975;6.20800;-29.68175;,
 35.00000;6.20800;-38.75000;,
 0.00000;6.20800;-38.75000;,
 0.00000;6.20800;-34.37500;,
 29.68175;6.20800;-17.34975;,
 38.75000;6.20800;-35.00000;,
 34.37500;6.20800;0.00000;,
 38.75000;6.20800;0.00000;,
 40.00000;4.95800;0.00000;,
 40.00000;4.95800;-36.25000;,
 40.00000;-0.04200;-0.00000;,
 40.00000;-0.04200;-36.25000;,
 36.25000;4.95800;-40.00000;,
 36.25000;-0.04200;-40.00000;,
 0.00000;4.95800;-40.00000;,
 0.00000;-0.04200;-40.00000;,
 0.00000;6.20800;34.37500;,
 0.00000;6.20800;38.75000;,
 35.00000;6.20800;38.75000;,
 17.34975;6.20800;29.68175;,
 38.75000;6.20800;35.00000;,
 29.68175;6.20800;17.34975;,
 40.00000;4.95800;36.25000;,
 40.00000;-0.04200;36.25000;,
 36.25000;4.95800;40.00000;,
 36.25000;-0.04200;40.00000;,
 0.00000;4.95800;40.00000;,
 0.00000;-0.04200;40.00000;,
 14.17750;36.60513;24.25475;,
 0.00000;40.95113;27.19125;,
 0.00000;64.68742;22.28337;,
 11.61852;61.12585;19.87687;,
 9.01830;86.04212;15.42850;,
 0.00000;88.80665;17.29638;,
 0.00000;112.54290;12.38848;,
 6.45932;110.56287;11.05060;,
 4.95708;124.95800;8.48053;,
 0.00000;124.95800;9.82143;,
 26.56137;23.68612;15.52575;,
 21.76712;50.53865;12.72338;,
 16.89562;77.82437;9.87590;,
 12.10145;104.67687;7.07360;,
 8.48053;124.95800;4.95708;,
 29.10250;31.70800;0.00000;,
 22.58925;63.20800;0.00000;,
 16.17950;94.20800;0.00000;,
 9.82143;124.95800;0.00000;,
 16.52250;79.91450;-9.65777;,
 8.48053;124.95800;-4.95708;,
 15.49575;23.97313;-26.51012;,
 23.06812;43.25188;-13.48388;,
 11.09880;66.10610;-18.98775;,
 4.95708;124.95800;-8.48053;,
 0.00000;15.03388;-32.55013;,
 0.00000;59.70338;-23.31388;,
 0.00000;124.95800;-9.82143;,
 33.36975;6.20800;3.71622;,
 15.18100;6.20800;25.97162;,
 0.00000;6.20800;30.07812;,
 0.00000;124.95800;4.91073;,
 2.47855;124.95800;4.24027;,
 25.97162;6.20800;15.18100;,
 4.24027;124.95800;2.47855;,
 30.07812;6.20800;0.00000;,
 4.91073;124.95800;0.00000;,
 25.97162;6.20800;-15.18100;,
 4.24027;124.95800;-2.47855;,
 15.18100;6.20800;-25.97162;,
 2.47855;124.95800;-4.24027;,
 0.00000;6.20800;-30.07812;,
 0.00000;124.95800;-4.91073;,
 0.00000;-0.04200;36.25000;,
 0.00000;6.20800;30.07812;,
 15.18100;6.20800;25.97162;,
 33.75000;-0.04200;36.25000;,
 36.25000;-0.04200;40.00000;,
 0.00000;-0.04200;40.00000;,
 37.50000;-0.04200;-0.00000;,
 30.07812;6.20800;0.00000;,
 25.97162;6.20800;-15.18100;,
 37.50000;-0.04200;-33.75000;,
 40.00000;-0.04200;-36.25000;,
 40.00000;-0.04200;-0.00000;,
 40.00000;-0.04200;36.25000;,
 37.50000;-0.04200;33.75000;,
 25.97162;6.20800;15.18100;,
 0.00000;-0.04200;-37.50000;,
 0.00000;-0.04200;-40.00000;,
 36.25000;-0.04200;-40.00000;,
 33.75000;-0.04200;-37.50000;,
 15.18100;6.20800;-25.97162;,
 0.00000;6.20800;-30.07812;,
 -35.00000;6.20800;-38.75000;,
 -17.34975;6.20800;-29.68175;,
 -38.75000;6.20800;-35.00000;,
 -29.68175;6.20800;-17.34975;,
 -38.75000;6.20800;0.00000;,
 -34.37500;6.20800;0.00000;,
 -40.00000;4.95800;-36.25000;,
 -40.00000;4.95800;0.00000;,
 -40.00000;-0.04200;-36.25000;,
 -40.00000;-0.04200;0.00000;,
 -36.25000;4.95800;-40.00000;,
 -36.25000;-0.04200;-40.00000;,
 -17.34975;6.20800;29.68175;,
 -35.00000;6.20800;38.75000;,
 -29.68175;6.20800;17.34975;,
 -38.75000;6.20800;35.00000;,
 -40.00000;4.95800;36.25000;,
 -40.00000;-0.04200;36.25000;,
 -36.25000;4.95800;40.00000;,
 -36.25000;-0.04200;40.00000;,
 -14.17750;36.60513;24.25475;,
 -9.01830;86.04212;15.42850;,
 -11.61852;61.12585;19.87687;,
 -4.95708;124.95800;8.48053;,
 -6.45932;110.56287;11.05060;,
 -26.56137;23.68612;15.52575;,
 -16.89562;77.82437;9.87590;,
 -21.76712;50.53865;12.72338;,
 -8.48053;124.95800;4.95708;,
 -12.10145;104.67687;7.07360;,
 -22.58925;63.20800;0.00000;,
 -29.10250;31.70800;0.00000;,
 -9.82143;124.95800;0.00000;,
 -16.17950;94.20800;0.00000;,
 -8.48053;124.95800;-4.95708;,
 -16.52250;79.91450;-9.65777;,
 -23.06812;43.25188;-13.48388;,
 -15.49575;23.97313;-26.51012;,
 -4.95708;124.95800;-8.48053;,
 -11.09880;66.10610;-18.98775;,
 -33.36975;6.20800;3.71622;,
 -2.47855;124.95800;4.24027;,
 -15.18100;6.20800;25.97162;,
 -4.24027;124.95800;2.47855;,
 -25.97162;6.20800;15.18100;,
 -4.91073;124.95800;0.00000;,
 -30.07812;6.20800;0.00000;,
 -4.24027;124.95800;-2.47855;,
 -25.97162;6.20800;-15.18100;,
 -2.47855;124.95800;-4.24027;,
 -15.18100;6.20800;-25.97162;,
 -33.75000;-0.04200;36.25000;,
 -15.18100;6.20800;25.97162;,
 -36.25000;-0.04200;40.00000;,
 -37.50000;-0.04200;-33.75000;,
 -25.97162;6.20800;-15.18100;,
 -30.07812;6.20800;0.00000;,
 -37.50000;-0.04200;0.00000;,
 -40.00000;-0.04200;0.00000;,
 -40.00000;-0.04200;-36.25000;,
 -37.50000;-0.04200;33.75000;,
 -40.00000;-0.04200;36.25000;,
 -25.97162;6.20800;15.18100;,
 -33.75000;-0.04200;-37.50000;,
 -36.25000;-0.04200;-40.00000;,
 -15.18100;6.20800;-25.97162;;
 
 138;
 4;0,1,2,3;,
 4;4,5,1,0;,
 4;6,7,5,4;,
 4;7,8,9,5;,
 4;8,10,11,9;,
 4;5,9,12,1;,
 4;9,11,13,12;,
 4;14,2,1,12;,
 4;12,13,15,14;,
 4;16,17,18,19;,
 4;19,18,20,21;,
 4;20,22,8,7;,
 4;22,23,10,8;,
 4;18,24,22,20;,
 4;24,25,23,22;,
 4;24,18,17,26;,
 4;26,27,25,24;,
 4;28,29,16,19;,
 4;30,31,32,33;,
 4;34,35,36,37;,
 4;38,28,19,21;,
 4;31,39,40,32;,
 4;35,41,42,36;,
 4;39,43,44,40;,
 4;41,45,46,42;,
 4;45,47,48,46;,
 4;49,50,4,0;,
 4;47,51,52,48;,
 4;53,49,0,3;,
 4;51,54,55,52;,
 4;31,30,29,28;,
 4;35,34,33,32;,
 4;39,31,28,38;,
 4;41,35,32,40;,
 4;45,41,40,44;,
 4;47,45,44,50;,
 4;51,47,50,49;,
 4;54,51,49,53;,
 3;56,38,21;,
 3;38,56,6;,
 3;6,56,7;,
 4;56,21,20,7;,
 3;43,6,4;,
 4;57,58,59,60;,
 4;60,59,37,36;,
 4;61,57,60,62;,
 4;62,60,36,42;,
 4;63,61,62,64;,
 4;64,62,42,46;,
 4;65,63,64,66;,
 4;66,64,46,48;,
 4;67,65,66,68;,
 4;68,66,48,52;,
 4;69,67,68,70;,
 4;70,68,52,55;,
 4;44,43,4,50;,
 4;39,38,6,43;,
 4;71,72,73,74;,
 4;71,74,75,76;,
 4;77,78,79,80;,
 4;77,80,81,82;,
 4;77,82,83,84;,
 4;77,84,85,78;,
 4;86,87,88,89;,
 4;86,89,90,91;,
 4;75,74,84,83;,
 4;73,85,84,74;,
 4;79,90,89,80;,
 4;80,89,88,81;,
 4;3,2,92,93;,
 4;93,92,94,95;,
 4;95,94,96,97;,
 4;94,98,99,96;,
 4;98,100,101,99;,
 4;92,102,98,94;,
 4;102,103,100,98;,
 4;102,92,2,14;,
 4;14,15,103,102;,
 4;104,105,17,16;,
 4;106,107,105,104;,
 4;96,99,108,107;,
 4;99,101,109,108;,
 4;107,108,110,105;,
 4;108,109,111,110;,
 4;26,17,105,110;,
 4;110,111,27,26;,
 4;104,16,29,112;,
 4;33,113,114,30;,
 4;37,115,116,34;,
 4;106,104,112,117;,
 4;113,118,119,114;,
 4;115,120,121,116;,
 4;118,122,123,119;,
 4;120,124,125,121;,
 4;124,126,127,125;,
 4;93,95,128,129;,
 4;126,130,131,127;,
 4;3,93,129,53;,
 4;130,55,54,131;,
 4;112,29,30,114;,
 4;113,33,34,116;,
 4;117,112,114,119;,
 4;118,113,116,121;,
 4;122,118,121,125;,
 4;128,122,125,127;,
 4;129,128,127,131;,
 4;53,129,131,54;,
 3;106,117,132;,
 3;97,132,117;,
 3;96,132,97;,
 4;96,107,106,132;,
 3;95,97,123;,
 4;133,59,58,134;,
 4;115,37,59,133;,
 4;135,133,134,136;,
 4;120,115,133,135;,
 4;137,135,136,138;,
 4;124,120,135,137;,
 4;139,137,138,140;,
 4;126,124,137,139;,
 4;141,139,140,142;,
 4;130,126,139,141;,
 4;70,141,142,69;,
 4;55,130,141,70;,
 4;128,95,123,122;,
 4;123,97,117,119;,
 4;143,144,72,71;,
 4;76,145,143,71;,
 4;146,147,148,149;,
 4;150,151,146,149;,
 4;152,153,150,149;,
 4;148,154,152,149;,
 4;155,156,87,86;,
 4;91,157,155,86;,
 4;153,152,143,145;,
 4;143,152,154,144;,
 4;146,155,157,147;,
 4;151,156,155,146;;
 
 MeshMaterialList {
  2;
  138;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.000000;0.749804;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.207059;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  136;
  0.000000;1.000000;0.000000;,
  0.000000;0.923880;-0.382683;,
  0.109792;0.947614;-0.299956;,
  0.299956;0.947614;-0.109792;,
  0.305102;0.952320;0.000000;,
  0.923880;0.382683;0.000000;,
  0.831155;0.448669;-0.328448;,
  0.923880;0.000000;-0.382683;,
  1.000000;0.000000;0.000000;,
  0.328448;0.448669;-0.831155;,
  0.382683;0.000000;-0.923880;,
  0.000000;0.382683;-0.923880;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.923880;0.382683;,
  0.109792;0.947614;0.299956;,
  0.299956;0.947614;0.109792;,
  0.831155;0.448669;0.328448;,
  0.923880;0.000000;0.382683;,
  0.328448;0.448669;0.831155;,
  0.382683;0.000000;0.923880;,
  0.000000;0.382683;0.923880;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.202484;0.979285;,
  -0.000000;0.202482;0.979286;,
  -0.000000;0.202483;0.979286;,
  0.000000;0.202485;0.979285;,
  0.000000;0.202485;0.979285;,
  0.490640;0.202514;0.847502;,
  0.490640;0.202513;0.847503;,
  0.490641;0.202513;0.847502;,
  0.490640;0.202514;0.847502;,
  0.490640;0.202514;0.847503;,
  0.872489;0.202193;0.444839;,
  0.847502;0.202514;0.490641;,
  0.847503;0.202513;0.490640;,
  0.847503;0.202513;0.490639;,
  0.847503;0.202513;0.490640;,
  0.946635;0.195729;0.256071;,
  0.979286;0.202484;-0.000001;,
  0.979286;0.202484;0.000001;,
  0.979286;0.202483;0.000001;,
  0.979286;0.202484;0.000001;,
  0.847503;0.202513;-0.490640;,
  0.847503;0.202514;-0.490639;,
  0.847503;0.202514;-0.490640;,
  0.490640;0.202513;-0.847503;,
  0.490638;0.202514;-0.847504;,
  0.490638;0.202513;-0.847504;,
  0.000000;0.202483;-0.979286;,
  -0.000000;0.202484;-0.979286;,
  0.000000;0.202483;-0.979286;,
  0.000000;-0.207331;0.978271;,
  0.000000;-0.207331;-0.978271;,
  -0.490130;-0.207361;-0.846625;,
  -0.846625;-0.207361;-0.490130;,
  -0.978271;-0.207331;0.000000;,
  -0.846625;-0.207361;0.490130;,
  -0.490130;-0.207361;0.846625;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.826700;0.562643;,
  0.000000;-0.785130;-0.619330;,
  -0.141325;-0.892665;-0.427992;,
  -0.378886;-0.912216;-0.155907;,
  -0.562643;-0.826700;0.000000;,
  -0.387806;-0.910121;0.145897;,
  -0.145897;-0.910121;0.387806;,
  0.000000;-0.945018;-0.327019;,
  -0.071719;-0.973490;-0.217196;,
  -0.191505;-0.978323;-0.078802;,
  -0.293810;-0.955864;0.000000;,
  -0.196365;-0.977744;0.073875;,
  0.000000;-0.955864;0.293810;,
  -0.073875;-0.977744;0.196365;,
  -0.109792;0.947614;-0.299956;,
  -0.299956;0.947614;-0.109792;,
  -0.305102;0.952320;0.000000;,
  -0.923880;0.382683;0.000000;,
  -0.831155;0.448669;-0.328448;,
  -0.923880;0.000000;-0.382683;,
  -1.000000;0.000000;0.000000;,
  -0.328448;0.448669;-0.831155;,
  -0.382683;0.000000;-0.923880;,
  -0.109792;0.947614;0.299956;,
  -0.299956;0.947614;0.109792;,
  -0.831155;0.448669;0.328448;,
  -0.923880;0.000000;0.382683;,
  -0.328448;0.448669;0.831155;,
  -0.382683;0.000000;0.923880;,
  -0.490640;0.202514;0.847502;,
  -0.490640;0.202513;0.847503;,
  -0.490641;0.202513;0.847502;,
  -0.490640;0.202514;0.847502;,
  -0.490640;0.202514;0.847503;,
  -0.872489;0.202193;0.444839;,
  -0.847502;0.202514;0.490641;,
  -0.847503;0.202513;0.490640;,
  -0.847503;0.202513;0.490639;,
  -0.847503;0.202513;0.490640;,
  -0.946635;0.195729;0.256071;,
  -0.979286;0.202484;-0.000001;,
  -0.979286;0.202484;0.000001;,
  -0.979286;0.202483;0.000001;,
  -0.979286;0.202484;0.000001;,
  -0.847503;0.202513;-0.490640;,
  -0.847503;0.202514;-0.490639;,
  -0.847503;0.202514;-0.490640;,
  -0.490640;0.202513;-0.847503;,
  -0.490638;0.202514;-0.847504;,
  -0.490638;0.202513;-0.847504;,
  0.490130;-0.207361;-0.846625;,
  0.846625;-0.207361;-0.490130;,
  0.978271;-0.207331;-0.000000;,
  0.846625;-0.207361;0.490130;,
  0.490130;-0.207361;0.846625;,
  0.141325;-0.892665;-0.427992;,
  0.378886;-0.912216;-0.155907;,
  0.562643;-0.826700;-0.000000;,
  0.387806;-0.910121;0.145897;,
  0.145897;-0.910121;0.387806;,
  0.071719;-0.973490;-0.217196;,
  0.191505;-0.978323;-0.078802;,
  0.293810;-0.955864;-0.000000;,
  0.196365;-0.977744;0.073875;,
  0.073875;-0.977744;0.196365;,
  0.000000;0.202484;0.979286;,
  0.490640;0.202512;0.847503;,
  0.847501;0.202509;0.490644;,
  0.887771;0.201677;-0.413749;,
  0.490642;0.202511;-0.847502;,
  0.000000;0.202480;-0.979286;,
  0.975490;0.201698;0.087957;,
  -0.490640;0.202512;0.847503;,
  -0.847501;0.202509;0.490644;,
  -0.490642;0.202511;-0.847502;,
  -0.887771;0.201677;-0.413749;,
  -0.975490;0.201698;0.087957;;
  138;
  4;0,2,1,0;,
  4;0,3,2,0;,
  4;0,4,3,0;,
  4;4,5,6,3;,
  4;5,8,7,6;,
  4;3,6,9,2;,
  4;6,7,10,9;,
  4;11,1,2,9;,
  4;9,10,12,11;,
  4;0,13,14,0;,
  4;0,14,15,0;,
  4;15,16,5,4;,
  4;16,17,8,5;,
  4;14,18,16,15;,
  4;18,19,17,16;,
  4;18,14,13,20;,
  4;20,21,19,18;,
  4;27,22,124,125;,
  4;23,28,29,24;,
  4;25,30,31,26;,
  4;32,27,125,126;,
  4;28,33,34,29;,
  4;30,35,36,31;,
  4;33,38,39,34;,
  4;35,40,41,36;,
  4;40,43,44,41;,
  4;45,42,127,128;,
  4;43,46,47,44;,
  4;48,45,128,129;,
  4;46,49,50,47;,
  4;28,23,22,27;,
  4;30,25,24,29;,
  4;33,28,27,32;,
  4;35,30,29,34;,
  4;40,35,34,39;,
  4;43,40,39,42;,
  4;46,43,42,45;,
  4;49,46,45,48;,
  3;37,32,126;,
  3;32,37,130;,
  3;0,0,4;,
  4;0,0,15,4;,
  3;38,130,127;,
  4;53,52,52,53;,
  4;0,0,0,0;,
  4;54,53,53,54;,
  4;0,0,0,0;,
  4;55,54,54,55;,
  4;0,0,0,0;,
  4;56,55,55,56;,
  4;0,0,0,0;,
  4;57,56,56,57;,
  4;0,0,0,0;,
  4;51,57,57,51;,
  4;0,0,0,0;,
  4;39,38,127,42;,
  4;33,32,130,38;,
  4;66,60,61,67;,
  4;66,67,58,58;,
  4;69,63,64,70;,
  4;69,70,58,58;,
  4;69,58,58,68;,
  4;69,68,62,63;,
  4;71,58,58,72;,
  4;71,72,65,59;,
  4;58,67,68,58;,
  4;61,62,68,67;,
  4;64,65,72,70;,
  4;70,72,58,58;,
  4;0,1,73,0;,
  4;0,73,74,0;,
  4;0,74,75,0;,
  4;74,77,76,75;,
  4;77,78,79,76;,
  4;73,80,77,74;,
  4;80,81,78,77;,
  4;80,73,1,11;,
  4;11,12,81,80;,
  4;0,82,13,0;,
  4;0,83,82,0;,
  4;75,76,84,83;,
  4;76,79,85,84;,
  4;83,84,86,82;,
  4;84,85,87,86;,
  4;20,13,82,86;,
  4;86,87,21,20;,
  4;131,124,22,88;,
  4;24,90,89,23;,
  4;26,92,91,25;,
  4;132,131,88,93;,
  4;90,95,94,89;,
  4;92,97,96,91;,
  4;95,100,99,94;,
  4;97,102,101,96;,
  4;102,105,104,101;,
  4;133,134,103,106;,
  4;105,108,107,104;,
  4;129,133,106,48;,
  4;108,50,49,107;,
  4;88,22,23,89;,
  4;90,24,25,91;,
  4;93,88,89,94;,
  4;95,90,91,96;,
  4;100,95,96,101;,
  4;103,100,101,104;,
  4;106,103,104,107;,
  4;48,106,107,49;,
  3;132,93,98;,
  3;135,98,93;,
  3;75,0,0;,
  4;75,83,0,0;,
  3;134,135,99;,
  4;109,52,52,109;,
  4;0,0,0,0;,
  4;110,109,109,110;,
  4;0,0,0,0;,
  4;111,110,110,111;,
  4;0,0,0,0;,
  4;112,111,111,112;,
  4;0,0,0,0;,
  4;113,112,112,113;,
  4;0,0,0,0;,
  4;51,113,113,51;,
  4;0,0,0,0;,
  4;103,134,99,100;,
  4;99,135,93,94;,
  4;119,114,60,66;,
  4;58,58,119,66;,
  4;122,117,116,121;,
  4;58,58,122,121;,
  4;120,58,58,121;,
  4;116,115,120,121;,
  4;123,58,58,71;,
  4;59,118,123,71;,
  4;58,120,119,58;,
  4;119,120,115,114;,
  4;122,123,118,117;,
  4;58,58,123,122;;
 }
 MeshTextureCoords {
  158;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
