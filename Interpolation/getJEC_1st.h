#include <cmath>
#include <iostream>

double getJEC_1st(const char * mode, double rawPt, double jetPt, double eta)
{
  double correction = 1;

  //JEC derived by Yaxian, v08 for pPb direction
  if(strcmp(mode,"pPb5")==0 || strcmp(mode,"pp5")==0)
  {
    static const float l2_data[][11] = {
    {-5, -3, 8, 7.29453, 199.44, 0.494839, 0.276511, -0.792857, 0.448071, 0.0123351, 0.137177},
    {-3, -2.5, 8, 11.5588, 310.821, 0.440008, 0.638357, 0.893406, 0.44229, 0.00247189, -0.143698},
    {-2.5, -2.043, 8, 10.029, 505.368, 0.467457, 0.520936, 1.11645, 0.472458, 0.00263514, -0.207679},
    {-2.043, -1.93, 8, 13.7701, 509.688, 0.469552, 0.498823, 1.14783, 0.469665, 0.000155723, -0.158303},
    {-1.93, -1.74, 8, 12.8794, 515.139, 0.471104, 0.460732, 1.18737, 0.476502, 0.000402041, -0.221769},
    {-1.74, -1.653, 8, 14.8682, 522.526, 0.456514, 0.486116, 1.10437, 0.454001, -0.00806557, -0.11941},
    {-1.653, -1.566, 8, 15.1293, 525.531, 0.473442, 0.399486, 1.25624, 0.470044, -0.0018738, -0.142698},
    {-1.566, -1.392, 8, 13.9055, 523.446, 0.501994, 0.205984, 1.52002, 0.496017, 0.000818876, -0.159213},
    {-1.392, -1.218, 8, 12.3865, 515.391, 0.474566, 0.407612, 1.25494, 0.465946, -0.013683, -0.0839901},
    {-1.218, -1.131, 8, 13.1405, 519.768, 0.47858, 0.383164, 1.2956, 0.469138, -0.0115013, -0.0852108},
    {-1.131, -0.957, 8, 13.0604, 525.934, 0.46597, 0.352694, 1.24776, 0.456691, -0.0164066, -0.0742335},
    {-0.957, -0.879, 8, 14.3084, 531.606, 0.466896, 0.312609, 1.27841, 0.457132, -0.0147493, -0.0756452},
    {-0.879, -0.783, 8, 14.1959, 530.075, 0.477799, 0.159985, 1.40549, 0.466966, -0.0131053, -0.0826476},
    {-0.783, -0.609, 8, 13.7843, 541.39, 0.488929, 0.0685645, 1.52071, 0.481177, -0.0054031, -0.129421},
    {-0.609, -0.522, 8, 13.3437, 539.557, 0.450359, 0.277844, 1.20149, 0.446158, -0.0178408, -0.102329},
    {-0.522, -0.435, 8, 14.5444, 541.079, 0.474432, 0.107487, 1.41959, 0.471165, -0.00974263, -0.147399},
    {-0.435, -0.348, 8, 13.5976, 542.438, 0.477241, 0.0721407, 1.43613, 0.474038, -0.0090166, -0.148653},
    {-0.348, -0.261, 8, 14.8324, 546.451, 0.506946, -0.146872, 1.70983, 0.501821, -0.000435964, -0.170627},
    {-0.261, -0.087, 8, 13.829, 540.936, 0.477215, 0.0950669, 1.43355, 0.474513, -0.00812045, -0.15635},
    {-0.087, 0, 8, 14.7221, 544.903, 0.464125, 0.174525, 1.32229, 0.463064, -0.0107499, -0.152861},
    {0, 0.087, 8, 14.1465, 546.558, 0.478855, 0.0721429, 1.45124, 0.476884, -0.00534718, -0.1677},
    {0.087, 0.261, 8, 14.7086, 546.053, 0.480804, 0.0571601, 1.47145, 0.478541, -0.00489973, -0.168299},
    {0.261, 0.348, 8, 14.109, 544.74, 0.47235, 0.113624, 1.38971, 0.472365, -0.0066212, -0.175276},
    {0.348, 0.435, 8, 13.5225, 542.137, 0.481527, 0.0639313, 1.46645, 0.480771, -0.0040829, -0.181345},
    {0.435, 0.522, 8, 13.6836, 530.358, 0.460224, 0.205546, 1.29808, 0.456101, -0.0126815, -0.119764},
    {0.522, 0.609, 8, 16.0573, 537.119, 0.469883, 0.13113, 1.37569, 0.468712, -0.00878941, -0.160895},
    {0.609, 0.783, 8, 14.4276, 528.332, 0.483635, 0.070158, 1.4753, 0.484458, -0.00358609, -0.198548},
    {0.783, 0.879, 8, 13.2065, 518.277, 0.461956, 0.259693, 1.27985, 0.455809, -0.0142577, -0.100542},
    {0.879, 0.957, 8, 13.4033, 510.526, 0.44849, 0.394049, 1.14544, 0.441721, -0.0199149, -0.0769729},
    {0.957, 1.131, 8, 12.8019, 504.388, 0.473818, 0.296703, 1.32144, 0.466881, -0.0116215, -0.107867},
    {1.131, 1.218, 8, 14.8397, 474.369, 0.478343, 0.367147, 1.31484, 0.471962, -0.0100558, -0.117245},
    {1.218, 1.392, 8, 12.3264, 482.578, 0.472902, 0.389902, 1.25652, 0.467402, -0.0119355, -0.113864},
    {1.392, 1.566, 8, 14.3366, 452.374, 0.472389, 0.388226, 1.24421, 0.471403, -0.00446652, -0.161732},
    {1.566, 1.653, 8, 11.8416, 302.442, 0.449406, 0.456842, 1.07749, 0.442758, -0.0157467, -0.0838603},
    {1.653, 1.74, 8, 13.9266, 299.711, 0.481703, 0.299692, 1.33695, 0.474303, -0.00391539, -0.124872},
    {1.74, 1.93, 8, 15.0453, 296.772, 0.437488, 0.553883, 0.942183, 0.432433, -0.0205602, -0.0742533},
    {1.93, 2.043, 8, 12.99, 290.476, 0.427948, 0.566345, 0.877226, 0.423518, -0.0242982, -0.0662429},
    {2.043, 2.5, 8, 10.4275, 318.176, 0.482521, 0.410412, 1.21586, 0.488536, 0.0166088, -0.239731},
    {2.5, 3, 8, 13.8058, 152.136, 0.34743, 0.793517, 0.328186, 0.343375, -0.0832196, 0.0379197},
    {3, 5, 8, 9.38857, 85.1421, 0.253474, 0.907463, -0.243946, 0.256755, -0.231361, 0.113664}
	};

    static const float l3_data[][12] = {
    {-5.191, 5.191, 9, 4, 5000, 1.05368, 0.0418261, -1.31229, 0.010568, -0.179949, 2.84977, -0.782686}
	};

    for (unsigned int i = 0; i < 40; i++)
    {
      if (eta >= l2_data[i][0] && eta < l2_data[i][1]) 
      {
        correction = 1;
        const float *p = &l2_data[i][5];
        const float x = rawPt;
        correction *= ((x>=20)*((p[0]+(p[1]/(pow(log10(x),2)+p[2])))+(p[3]*exp(-(p[4]*((log10(x)-p[5])*(log10(x)-p[5])))))))+((x<20)*1);;
        p = &l3_data[0][5];
        correction *= p[0]+p[1]/(pow(log10(x),2)+p[2])+p[3]*exp((-p[4]*(log10(x)-p[5])*(log10(x)-p[5]))+(p[6]*(log10(x)-p[5])));
        break;
      }
    }   
    return rawPt*correction;
  }
  //JEC derived by Yaxian, v17 for Pbp direction
  else if(strcmp(mode,"Pbp5")==0)
  {
    static const float l2_data_1[][11] = {
    {-5, -3, 8, 20.9494, 142.562, 0.397055, 0.621114, 0.606799, 0.38662, -0.0887771, 0.0460021},
    {-3, -2.5, 8, 15.4947, 158.637, 0.121365, -0.422885, 3.30823, 1.02671, 0.194477, 1.383},
    {-2.5, -2.243, 8, 16.0786, 206.34, 0.576557, -0.435602, 0.767615, 0.750493, 0.0813181, -0.00265938},
    {-2.243, -1.93, 8, 17.8047, 297.859, 0.626572, -0.612674, 3.27614, 0.622391, 0.039351, -0.476973},
    {-1.93, -1.74, 8, 16.9472, 299.687, 0.500762, 0.240909, 1.65515, 0.488171, 0.00427765, -0.111224},
    {-1.74, -1.553, 8, 19.4427, 516.889, 0.475285, 0.275516, 1.46987, 0.459348, -0.0236147, -0.00829985},
    {-1.553, -1.392, 8, 18.815, 499.087, 0.525765, -0.0141155, 1.99741, 0.508772, 0.00487632, -0.100551},
    {-1.392, -1.131, 8, 17.6791, 456.35, 0.541308, -0.0345176, 2.16323, 0.52305, 0.00957549, -0.114932},
    {-1.131, -0.879, 8, 17.1671, 516.163, 0.59016, -0.549979, 2.83937, 0.583839, 0.023846, -0.360665},
    {-0.879, -0.609, 8, 17.7765, 525.119, 0.516859, -0.0525546, 1.97725, 0.501015, 0.00687127, -0.102051},
    {-0.609, -0.522, 8, 17.1145, 509.782, 0.46658, 0.174402, 1.52013, 0.450884, -0.0184007, -0.0149639},
    {-0.522, -0.435, 8, 18.055, 533.637, 0.665321, -1.35247, 3.01336, 0.663477, 0.0508586, -0.176136},
    {-0.435, -0.348, 8, 18.9764, 524.666, 0.65259, -1.24649, 3.58731, 0.61218, 0.039421, -0.151576},
    {-0.348, -0.261, 8, 18.7267, 505.638, 0.549697, -0.376181, 2.3728, 0.527632, 0.00996702, -0.0926022},
    {-0.261, -0.087, 8, 17.9307, 529.947, 0.477424, 0.115184, 1.60203, 0.461564, -0.0127118, -0.0332461},
    {-0.087, 0, 8, 18.3132, 539.987, 0.525164, -0.151212, 2.07113, 0.507833, 0.00906075, -0.104707},
    {0, 0.087, 8, 18.5845, 550.553, 0.46183, 0.201631, 1.44671, 0.448233, -0.0170974, -0.0320008},
    {0.087, 0.261, 8, 17.9564, 565.123, 0.458134, 0.219033, 1.41524, 0.446321, -0.0140534, -0.046613},
    {0.261, 0.348, 8, 18.6754, 544.04, 0.48739, 0.0895345, 1.67164, 0.468042, -0.0048837, -0.0297221},
    {0.348, 0.435, 8, 18.3028, 545.735, 0.553397, -0.334837, 2.36972, 0.53417, 0.0175732, -0.133825},
    {0.435, 0.522, 8, 18.1073, 516.688, 0.506145, -0.0523548, 1.89123, 0.486999, -0.0032065, -0.0476872},
    {0.522, 0.609, 8, 18.7352, 538.735, 0.533178, -0.237506, 2.16338, 0.513586, 0.00822483, -0.0914904},
    {0.609, 0.879, 8, 18.3687, 568.972, 0.556382, -0.322974, 2.38514, 0.538208, 0.0167073, -0.144766},
    {0.879, 1.131, 8, 17.8637, 515.13, 0.492424, 0.159862, 1.67279, 0.476868, -0.00969435, -0.0515374},
    {1.131, 1.392, 8, 18.5599, 516.65, 0.664873, -0.864739, 1.46247, 0.756289, 0.0574531, -0.323984},
    {1.392, 1.553, 8, 18.0191, 519.413, 0.660889, -1.11176, 3.77063, 0.656929, 0.0335571, -0.568288},
    {1.553, 1.74, 8, 16.2636, 524.989, 0.625011, -0.62645, 3.22383, 0.581068, 0.0392119, -0.040577},
    {1.74, 1.93, 8, 17.747, 509.352, 0.655161, -0.823391, 3.60988, 0.617062, 0.0452533, -0.190398},
    {1.93, 2.243, 8, 15.6122, 503.1, 0.632406, -0.63156, 3.388, 0.598343, 0.0418872, -0.176055},
    {2.243, 2.5, 8, 15.4238, 508.321, 0.649389, -0.734386, 3.0006, 0.634106, 0.0591195, -0.116671},
    {2.5, 3, 8, 17.4344, 492.834, 0.660892, -0.109437, -0.537924, 0.581253, 0.0889376, 0.00742166},
    {3, 5, 8, 8.74526, 285.872, 0.486494, -1.17782, 4.12418, 0.868344, 0.135141, 0.641498}
	};

    static const float l3_data_1[][12] = {
    {-5.191, 5.191, 9, 4, 5000, 1.05475, 0.0361301, 0.0225288, 0.00417097, 4.98344, 1.70233, -1.80036}
	};

    for (unsigned int i = 0; i < 40; i++)
    {
      if (eta >= l2_data_1[i][0] && eta < l2_data_1[i][1]) 
      {   
        correction = 1;
        const float *q = &l2_data_1[i][5];
        const float x = rawPt;
        correction *= (q[0]+(q[1]/(pow(log10(x),2)+q[2])))+(q[3]*exp(-(q[4]*((log10(x)-q[5])*(log10(x)-q[5])))));
        q = &l3_data_1[0][5];
        correction *= q[0]+q[1]/(pow(log10(x),2)+q[2])+q[3]*exp((-q[4]*(log10(x)-q[5])*(log10(x)-q[5]))+(q[6]*(log10(x)-q[5])));
        break;
      }
    }   
    return rawPt*correction;
  }
  //just use JEC in forest for non-Pb systems
  else return jetPt;
}
