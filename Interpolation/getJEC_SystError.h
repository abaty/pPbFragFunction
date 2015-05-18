#include <cmath>
#include <iostream>
#include "TMath.h"
#include "getJEC_L2L3res.h"

double getJEC_SystError(const char * mode, double jetPt, double eta, bool isRelative)
{
  //2011 Legacy JEC uncertainty as a function of eta/pt
  const double syst5TeV[18][120] = {{-2.4, -2.1,117, 9,0.0958,0.0958,11,0.0744,0.0744, 13.5,0.0597,0.0597, 16.5,0.0499,0.0499, 19.5,0.044,0.044, 22.5,0.0402,0.0402,26,0.037,0.037,30,0.0343,0.0343, 34.5,0.0322,0.0322,40,0.0302,0.0302,46,0.0288,0.0288, 52.5,0.0277,0.0277,60,0.0268,0.0268,69,0.0262,0.0262,79,0.0257,0.0257, 90.5,0.0254,0.0254,105.5,0.0252,0.0252,123.5,0.0251,0.0251,143,0.025,0.025,163.5,0.0249,0.0249,185,0.0249,0.0249,208,0.0249,0.0249,232.5,0.0249,0.0249,258.5,0.025,0.025,286,0.025,0.025,331,0.0251,0.0251,396,0.0251,0.0251,468.5,0.0252,0.0252,549.5,0.0253,0.0253,639,0.0255,0.0255,738,0.0256,0.0256,847.5,0.0257,0.0257,968.5,0.0259,0.0259, 1102,0.026,0.026,1249.5,0.0262,0.0262, 1412,0.0264,0.0264,1590.5,0.0265,0.0265, 1787,0.0267,0.0267,1944.5,0.0268,0.0268},
{-2.1, -1.8,117, 9,0.0958,0.0958,11,0.0744,0.0744, 13.5,0.0597,0.0597, 16.5,0.0499,0.0499, 19.5,0.044,0.044, 22.5,0.0402,0.0402,26,0.037,0.037,30,0.0343,0.0343, 34.5,0.0322,0.0322,40,0.0302,0.0302,46,0.0288,0.0288, 52.5,0.0277,0.0277,60,0.0268,0.0268,69,0.0262,0.0262,79,0.0257,0.0257, 90.5,0.0254,0.0254,105.5,0.0252,0.0252,123.5,0.0251,0.0251,143,0.025,0.025,163.5,0.0249,0.0249,185,0.0249,0.0249,208,0.0249,0.0249,232.5,0.0249,0.0249,258.5,0.025,0.025,286,0.025,0.025,331,0.0251,0.0251,396,0.0251,0.0251,468.5,0.0252,0.0252,549.5,0.0253,0.0253,639,0.0255,0.0255,738,0.0256,0.0256,847.5,0.0257,0.0257,968.5,0.0259,0.0259, 1102,0.026,0.026,1249.5,0.0262,0.0262, 1412,0.0264,0.0264,1590.5,0.0265,0.0265, 1787,0.0267,0.0267,1944.5,0.0268,0.0268},
{-1.8, -1.5,117, 9,0.0958,0.0958,11,0.0744,0.0744, 13.5,0.0597,0.0597, 16.5,0.0499,0.0499, 19.5,0.044,0.044, 22.5,0.0402,0.0402,26,0.037,0.037,30,0.0343,0.0343, 34.5,0.0322,0.0322,40,0.0302,0.0302,46,0.0288,0.0288, 52.5,0.0277,0.0277,60,0.0268,0.0268,69,0.0262,0.0262,79,0.0257,0.0257, 90.5,0.0254,0.0254,105.5,0.0252,0.0252,123.5,0.0251,0.0251,143,0.025,0.025,163.5,0.0249,0.0249,185,0.0249,0.0249,208,0.0249,0.0249,232.5,0.0249,0.0249,258.5,0.025,0.025,286,0.025,0.025,331,0.0251,0.0251,396,0.0251,0.0251,468.5,0.0252,0.0252,549.5,0.0253,0.0253,639,0.0255,0.0255,738,0.0256,0.0256,847.5,0.0257,0.0257,968.5,0.0259,0.0259, 1102,0.026,0.026,1249.5,0.0262,0.0262, 1412,0.0264,0.0264,1590.5,0.0265,0.0265, 1787,0.0267,0.0267,1944.5,0.0268,0.0268},
{-1.5, -1.3,117, 9,0.0958,0.0958,11,0.0744,0.0744, 13.5,0.0597,0.0597, 16.5,0.0499,0.0499, 19.5,0.044,0.044, 22.5,0.0402,0.0402,26,0.037,0.037,30,0.0343,0.0343, 34.5,0.0322,0.0322,40,0.0302,0.0302,46,0.0288,0.0288, 52.5,0.0277,0.0277,60,0.0268,0.0268,69,0.0262,0.0262,79,0.0257,0.0257, 90.5,0.0254,0.0254,105.5,0.0252,0.0252,123.5,0.0251,0.0251,143,0.025,0.025,163.5,0.0249,0.0249,185,0.0249,0.0249,208,0.0249,0.0249,232.5,0.0249,0.0249,258.5,0.025,0.025,286,0.025,0.025,331,0.0251,0.0251,396,0.0251,0.0251,468.5,0.0252,0.0252,549.5,0.0253,0.0253,639,0.0255,0.0255,738,0.0256,0.0256,847.5,0.0257,0.0257,968.5,0.0259,0.0259, 1102,0.026,0.026,1249.5,0.0262,0.0262, 1412,0.0264,0.0264,1590.5,0.0265,0.0265, 1787,0.0267,0.0267,1944.5,0.0268,0.0268},
{-1.3, -1.1,117, 9,0.0946,0.0946,11,0.0728,0.0728, 13.5,0.0578,0.0578, 16.5,0.0476,0.0476, 19.5,0.0414,0.0414, 22.5,0.0373,0.0373,26,0.0338,0.0338,30,0.0309,0.0309, 34.5,0.0284,0.0284,40,0.0262,0.0262,46,0.0246,0.0246, 52.5,0.0232,0.0232,60,0.0222,0.0222,69,0.0214,0.0214,79,0.0209,0.0209, 90.5,0.0205,0.0205,105.5,0.0202,0.0202,123.5,0.0201,0.0201,143, 0.02, 0.02,163.5,0.0199,0.0199,185,0.0199,0.0199,208,0.0199,0.0199,232.5,0.0199,0.0199,258.5, 0.02, 0.02,286, 0.02, 0.02,331,0.0201,0.0201,396,0.0201,0.0201,468.5,0.0202,0.0202,549.5,0.0204,0.0204,639,0.0206,0.0206,738,0.0207,0.0207,847.5,0.0209,0.0209,968.5,0.0211,0.0211, 1102,0.0213,0.0213,1249.5,0.0215,0.0215, 1412,0.0217,0.0217,1590.5,0.0219,0.0219, 1787,0.0221,0.0221,1944.5,0.0223,0.0223},
{-1.1, -0.9,117, 9,0.0946,0.0946,11,0.0728,0.0728, 13.5,0.0578,0.0578, 16.5,0.0476,0.0476, 19.5,0.0414,0.0414, 22.5,0.0373,0.0373,26,0.0338,0.0338,30,0.0309,0.0309, 34.5,0.0284,0.0284,40,0.0262,0.0262,46,0.0246,0.0246, 52.5,0.0232,0.0232,60,0.0222,0.0222,69,0.0214,0.0214,79,0.0209,0.0209, 90.5,0.0205,0.0205,105.5,0.0202,0.0202,123.5,0.0201,0.0201,143, 0.02, 0.02,163.5,0.0199,0.0199,185,0.0199,0.0199,208,0.0199,0.0199,232.5,0.0199,0.0199,258.5, 0.02, 0.02,286, 0.02, 0.02,331,0.0201,0.0201,396,0.0201,0.0201,468.5,0.0202,0.0202,549.5,0.0204,0.0204,639,0.0206,0.0206,738,0.0207,0.0207,847.5,0.0209,0.0209,968.5,0.0211,0.0211, 1102,0.0213,0.0213,1249.5,0.0215,0.0215, 1412,0.0217,0.0217,1590.5,0.0219,0.0219, 1787,0.0221,0.0221,1944.5,0.0223,0.0223},
{-0.9, -0.6,117, 9,0.0946,0.0946,11,0.0728,0.0728, 13.5,0.0578,0.0578, 16.5,0.0476,0.0476, 19.5,0.0414,0.0414, 22.5,0.0373,0.0373,26,0.0338,0.0338,30,0.0309,0.0309, 34.5,0.0284,0.0284,40,0.0262,0.0262,46,0.0246,0.0246, 52.5,0.0232,0.0232,60,0.0222,0.0222,69,0.0214,0.0214,79,0.0209,0.0209, 90.5,0.0205,0.0205,105.5,0.0202,0.0202,123.5,0.0201,0.0201,143, 0.02, 0.02,163.5,0.0199,0.0199,185,0.0199,0.0199,208,0.0199,0.0199,232.5,0.0199,0.0199,258.5, 0.02, 0.02,286, 0.02, 0.02,331,0.0201,0.0201,396,0.0201,0.0201,468.5,0.0202,0.0202,549.5,0.0204,0.0204,639,0.0206,0.0206,738,0.0207,0.0207,847.5,0.0209,0.0209,968.5,0.0211,0.0211, 1102,0.0213,0.0213,1249.5,0.0215,0.0215, 1412,0.0217,0.0217,1590.5,0.0219,0.0219, 1787,0.0221,0.0221,1944.5,0.0223,0.0223},
{-0.6, -0.3,117, 9,0.0946,0.0946,11,0.0728,0.0728, 13.5,0.0578,0.0578, 16.5,0.0476,0.0476, 19.5,0.0414,0.0414, 22.5,0.0373,0.0373,26,0.0338,0.0338,30,0.0309,0.0309, 34.5,0.0284,0.0284,40,0.0262,0.0262,46,0.0246,0.0246, 52.5,0.0232,0.0232,60,0.0222,0.0222,69,0.0214,0.0214,79,0.0209,0.0209, 90.5,0.0205,0.0205,105.5,0.0202,0.0202,123.5,0.0201,0.0201,143, 0.02, 0.02,163.5,0.0199,0.0199,185,0.0199,0.0199,208,0.0199,0.0199,232.5,0.0199,0.0199,258.5, 0.02, 0.02,286, 0.02, 0.02,331,0.0201,0.0201,396,0.0201,0.0201,468.5,0.0202,0.0202,549.5,0.0204,0.0204,639,0.0206,0.0206,738,0.0207,0.0207,847.5,0.0209,0.0209,968.5,0.0211,0.0211, 1102,0.0213,0.0213,1249.5,0.0215,0.0215, 1412,0.0217,0.0217,1590.5,0.0219,0.0219, 1787,0.0221,0.0221,1944.5,0.0223,0.0223},
{-0.3, 0,117, 9,0.0946,0.0946,11,0.0728,0.0728, 13.5,0.0578,0.0578, 16.5,0.0476,0.0476, 19.5,0.0414,0.0414, 22.5,0.0373,0.0373,26,0.0338,0.0338,30,0.0309,0.0309, 34.5,0.0284,0.0284,40,0.0262,0.0262,46,0.0246,0.0246, 52.5,0.0232,0.0232,60,0.0222,0.0222,69,0.0214,0.0214,79,0.0209,0.0209, 90.5,0.0205,0.0205,105.5,0.0202,0.0202,123.5,0.0201,0.0201,143, 0.02, 0.02,163.5,0.0199,0.0199,185,0.0199,0.0199,208,0.0199,0.0199,232.5,0.0199,0.0199,258.5, 0.02, 0.02,286, 0.02, 0.02,331,0.0201,0.0201,396,0.0201,0.0201,468.5,0.0202,0.0202,549.5,0.0204,0.0204,639,0.0206,0.0206,738,0.0207,0.0207,847.5,0.0209,0.0209,968.5,0.0211,0.0211, 1102,0.0213,0.0213,1249.5,0.0215,0.0215, 1412,0.0217,0.0217,1590.5,0.0219,0.0219, 1787,0.0221,0.0221,1944.5,0.0223,0.0223},
{0,0.3,117, 9,0.0946,0.0946,11,0.0728,0.0728, 13.5,0.0578,0.0578, 16.5,0.0476,0.0476, 19.5,0.0414,0.0414, 22.5,0.0373,0.0373,26,0.0338,0.0338,30,0.0309,0.0309, 34.5,0.0284,0.0284,40,0.0262,0.0262,46,0.0246,0.0246, 52.5,0.0232,0.0232,60,0.0222,0.0222,69,0.0214,0.0214,79,0.0209,0.0209, 90.5,0.0205,0.0205,105.5,0.0202,0.0202,123.5,0.0201,0.0201,143, 0.02, 0.02,163.5,0.0199,0.0199,185,0.0199,0.0199,208,0.0199,0.0199,232.5,0.0199,0.0199,258.5, 0.02, 0.02,286, 0.02, 0.02,331,0.0201,0.0201,396,0.0201,0.0201,468.5,0.0202,0.0202,549.5,0.0204,0.0204,639,0.0206,0.0206,738,0.0207,0.0207,847.5,0.0209,0.0209,968.5,0.0211,0.0211, 1102,0.0213,0.0213,1249.5,0.0215,0.0215, 1412,0.0217,0.0217,1590.5,0.0219,0.0219, 1787,0.0221,0.0221,1944.5,0.0223,0.0223},
{0.3,0.6,117, 9,0.0946,0.0946,11,0.0728,0.0728, 13.5,0.0578,0.0578, 16.5,0.0476,0.0476, 19.5,0.0414,0.0414, 22.5,0.0373,0.0373,26,0.0338,0.0338,30,0.0309,0.0309, 34.5,0.0284,0.0284,40,0.0262,0.0262,46,0.0246,0.0246, 52.5,0.0232,0.0232,60,0.0222,0.0222,69,0.0214,0.0214,79,0.0209,0.0209, 90.5,0.0205,0.0205,105.5,0.0202,0.0202,123.5,0.0201,0.0201,143, 0.02, 0.02,163.5,0.0199,0.0199,185,0.0199,0.0199,208,0.0199,0.0199,232.5,0.0199,0.0199,258.5, 0.02, 0.02,286, 0.02, 0.02,331,0.0201,0.0201,396,0.0201,0.0201,468.5,0.0202,0.0202,549.5,0.0204,0.0204,639,0.0206,0.0206,738,0.0207,0.0207,847.5,0.0209,0.0209,968.5,0.0211,0.0211, 1102,0.0213,0.0213,1249.5,0.0215,0.0215, 1412,0.0217,0.0217,1590.5,0.0219,0.0219, 1787,0.0221,0.0221,1944.5,0.0223,0.0223},
{0.6,0.9,117, 9,0.0946,0.0946,11,0.0728,0.0728, 13.5,0.0578,0.0578, 16.5,0.0476,0.0476, 19.5,0.0414,0.0414, 22.5,0.0373,0.0373,26,0.0338,0.0338,30,0.0309,0.0309, 34.5,0.0284,0.0284,40,0.0262,0.0262,46,0.0246,0.0246, 52.5,0.0232,0.0232,60,0.0222,0.0222,69,0.0214,0.0214,79,0.0209,0.0209, 90.5,0.0205,0.0205,105.5,0.0202,0.0202,123.5,0.0201,0.0201,143, 0.02, 0.02,163.5,0.0199,0.0199,185,0.0199,0.0199,208,0.0199,0.0199,232.5,0.0199,0.0199,258.5, 0.02, 0.02,286, 0.02, 0.02,331,0.0201,0.0201,396,0.0201,0.0201,468.5,0.0202,0.0202,549.5,0.0204,0.0204,639,0.0206,0.0206,738,0.0207,0.0207,847.5,0.0209,0.0209,968.5,0.0211,0.0211, 1102,0.0213,0.0213,1249.5,0.0215,0.0215, 1412,0.0217,0.0217,1590.5,0.0219,0.0219, 1787,0.0221,0.0221,1944.5,0.0223,0.0223},
{0.9,1.1,117, 9,0.0946,0.0946,11,0.0728,0.0728, 13.5,0.0578,0.0578, 16.5,0.0476,0.0476, 19.5,0.0414,0.0414, 22.5,0.0373,0.0373,26,0.0338,0.0338,30,0.0309,0.0309, 34.5,0.0284,0.0284,40,0.0262,0.0262,46,0.0246,0.0246, 52.5,0.0232,0.0232,60,0.0222,0.0222,69,0.0214,0.0214,79,0.0209,0.0209, 90.5,0.0205,0.0205,105.5,0.0202,0.0202,123.5,0.0201,0.0201,143, 0.02, 0.02,163.5,0.0199,0.0199,185,0.0199,0.0199,208,0.0199,0.0199,232.5,0.0199,0.0199,258.5, 0.02, 0.02,286, 0.02, 0.02,331,0.0201,0.0201,396,0.0201,0.0201,468.5,0.0202,0.0202,549.5,0.0204,0.0204,639,0.0206,0.0206,738,0.0207,0.0207,847.5,0.0209,0.0209,968.5,0.0211,0.0211, 1102,0.0213,0.0213,1249.5,0.0215,0.0215, 1412,0.0217,0.0217,1590.5,0.0219,0.0219, 1787,0.0221,0.0221,1944.5,0.0223,0.0223},
{1.1,1.3,117, 9,0.0946,0.0946,11,0.0728,0.0728, 13.5,0.0578,0.0578, 16.5,0.0476,0.0476, 19.5,0.0414,0.0414, 22.5,0.0373,0.0373,26,0.0338,0.0338,30,0.0309,0.0309, 34.5,0.0284,0.0284,40,0.0262,0.0262,46,0.0246,0.0246, 52.5,0.0232,0.0232,60,0.0222,0.0222,69,0.0214,0.0214,79,0.0209,0.0209, 90.5,0.0205,0.0205,105.5,0.0202,0.0202,123.5,0.0201,0.0201,143, 0.02, 0.02,163.5,0.0199,0.0199,185,0.0199,0.0199,208,0.0199,0.0199,232.5,0.0199,0.0199,258.5, 0.02, 0.02,286, 0.02, 0.02,331,0.0201,0.0201,396,0.0201,0.0201,468.5,0.0202,0.0202,549.5,0.0204,0.0204,639,0.0206,0.0206,738,0.0207,0.0207,847.5,0.0209,0.0209,968.5,0.0211,0.0211, 1102,0.0213,0.0213,1249.5,0.0215,0.0215, 1412,0.0217,0.0217,1590.5,0.0219,0.0219, 1787,0.0221,0.0221,1944.5,0.0223,0.0223},
{1.3,1.5,117, 9,0.0958,0.0958,11,0.0744,0.0744, 13.5,0.0597,0.0597, 16.5,0.0499,0.0499, 19.5,0.044,0.044, 22.5,0.0402,0.0402,26,0.037,0.037,30,0.0343,0.0343, 34.5,0.0322,0.0322,40,0.0302,0.0302,46,0.0288,0.0288, 52.5,0.0277,0.0277,60,0.0268,0.0268,69,0.0262,0.0262,79,0.0257,0.0257, 90.5,0.0254,0.0254,105.5,0.0252,0.0252,123.5,0.0251,0.0251,143,0.025,0.025,163.5,0.0249,0.0249,185,0.0249,0.0249,208,0.0249,0.0249,232.5,0.0249,0.0249,258.5,0.025,0.025,286,0.025,0.025,331,0.0251,0.0251,396,0.0251,0.0251,468.5,0.0252,0.0252,549.5,0.0253,0.0253,639,0.0255,0.0255,738,0.0256,0.0256,847.5,0.0257,0.0257,968.5,0.0259,0.0259, 1102,0.026,0.026,1249.5,0.0262,0.0262, 1412,0.0264,0.0264,1590.5,0.0265,0.0265, 1787,0.0267,0.0267,1944.5,0.0268,0.0268},
{1.5,1.8,117, 9,0.0958,0.0958,11,0.0744,0.0744, 13.5,0.0597,0.0597, 16.5,0.0499,0.0499, 19.5,0.044,0.044, 22.5,0.0402,0.0402,26,0.037,0.037,30,0.0343,0.0343, 34.5,0.0322,0.0322,40,0.0302,0.0302,46,0.0288,0.0288, 52.5,0.0277,0.0277,60,0.0268,0.0268,69,0.0262,0.0262,79,0.0257,0.0257, 90.5,0.0254,0.0254,105.5,0.0252,0.0252,123.5,0.0251,0.0251,143,0.025,0.025,163.5,0.0249,0.0249,185,0.0249,0.0249,208,0.0249,0.0249,232.5,0.0249,0.0249,258.5,0.025,0.025,286,0.025,0.025,331,0.0251,0.0251,396,0.0251,0.0251,468.5,0.0252,0.0252,549.5,0.0253,0.0253,639,0.0255,0.0255,738,0.0256,0.0256,847.5,0.0257,0.0257,968.5,0.0259,0.0259, 1102,0.026,0.026,1249.5,0.0262,0.0262, 1412,0.0264,0.0264,1590.5,0.0265,0.0265, 1787,0.0267,0.0267,1944.5,0.0268,0.0268},
{1.8,2.1,117, 9,0.0958,0.0958,11,0.0744,0.0744, 13.5,0.0597,0.0597, 16.5,0.0499,0.0499, 19.5,0.044,0.044, 22.5,0.0402,0.0402,26,0.037,0.037,30,0.0343,0.0343, 34.5,0.0322,0.0322,40,0.0302,0.0302,46,0.0288,0.0288, 52.5,0.0277,0.0277,60,0.0268,0.0268,69,0.0262,0.0262,79,0.0257,0.0257, 90.5,0.0254,0.0254,105.5,0.0252,0.0252,123.5,0.0251,0.0251,143,0.025,0.025,163.5,0.0249,0.0249,185,0.0249,0.0249,208,0.0249,0.0249,232.5,0.0249,0.0249,258.5,0.025,0.025,286,0.025,0.025,331,0.0251,0.0251,396,0.0251,0.0251,468.5,0.0252,0.0252,549.5,0.0253,0.0253,639,0.0255,0.0255,738,0.0256,0.0256,847.5,0.0257,0.0257,968.5,0.0259,0.0259, 1102,0.026,0.026,1249.5,0.0262,0.0262, 1412,0.0264,0.0264,1590.5,0.0265,0.0265, 1787,0.0267,0.0267,1944.5,0.0268,0.0268},
{2.1,2.4,117, 9,0.0958,0.0958,11,0.0744,0.0744, 13.5,0.0597,0.0597, 16.5,0.0499,0.0499, 19.5,0.044,0.044, 22.5,0.0402,0.0402,26,0.037,0.037,30,0.0343,0.0343, 34.5,0.0322,0.0322,40,0.0302,0.0302,46,0.0288,0.0288, 52.5,0.0277,0.0277,60,0.0268,0.0268,69,0.0262,0.0262,79,0.0257,0.0257, 90.5,0.0254,0.0254,105.5,0.0252,0.0252,123.5,0.0251,0.0251,143,0.025,0.025,163.5,0.0249,0.0249,185,0.0249,0.0249,208,0.0249,0.0249,232.5,0.0249,0.0249,258.5,0.025,0.025,286,0.025,0.025,331,0.0251,0.0251,396,0.0251,0.0251,468.5,0.0252,0.0252,549.5,0.0253,0.0253,639,0.0255,0.0255,738,0.0256,0.0256,847.5,0.0257,0.0257,968.5,0.0259,0.0259, 1102,0.026,0.026,1249.5,0.0262,0.0262, 1412,0.0264,0.0264,1590.5,0.0265,0.0265, 1787,0.0267,0.0267,1944.5,0.0268,0.0268}}; 

  //2014 Winter JEC uncertainty as a function of eta/pt
  const double syst7TeV[24][135] = {{-2.4,-2.2,132,9.0,0.1064,0.1064,11.0,0.0844,0.0844,13.5,0.0661,0.0661,16.5,0.0542,0.0542,19.5,0.0432,0.0432,22.5,0.0369,0.0369,26.0,0.0317,0.0317,30.0,0.0278,0.0278,34.5,0.0238,0.0238,40.0,0.0205,0.0205,46.0,0.0180,0.0180,52.5,0.0162,0.0162,60.0,0.0149,0.0149,69.0,0.0137,0.0137,79.0,0.0127,0.0127,90.5,0.0119,0.0119,105.5,0.0111,0.0111,123.5,0.0104,0.0104,143.0,0.0099,0.0099,163.5,0.0095,0.0095,185.0,0.0091,0.0091,208.0,0.0089,0.0089,232.5,0.0087,0.0087,258.5,0.0086,0.0086,286.0,0.0085,0.0085,331.0,0.0085,0.0085,396.0,0.0086,0.0086,468.5,0.0088,0.0088,549.5,0.0091,0.0091,639.0,0.0095,0.0095,738.0,0.0100,0.0100,847.5,0.0104,0.0104,968.5,0.0107,0.0107,1102.0,0.0111,0.0111,1249.5,0.0115,0.0115,1412.0,0.0119,0.0119,1590.5,0.0123,0.0123,1787.0,0.0127,0.0127,1945.0,0.0130,0.0130,2119.0,0.0133,0.0133,2369.0,0.0137,0.0137,2643.5,0.0141,0.0141,2945.0,0.0144,0.0144,3276.5,0.0148,0.0148},
{-2.2,-2.0,132,9.0,0.1103,0.1103,11.0,0.0867,0.0867,13.5,0.0715,0.0715,16.5,0.0553,0.0553,19.5,0.0459,0.0459,22.5,0.0393,0.0393,26.0,0.0339,0.0339,30.0,0.0297,0.0297,34.5,0.0256,0.0256,40.0,0.0221,0.0221,46.0,0.0195,0.0195,52.5,0.0177,0.0177,60.0,0.0163,0.0163,69.0,0.0150,0.0150,79.0,0.0138,0.0138,90.5,0.0128,0.0128,105.5,0.0118,0.0118,123.5,0.0109,0.0109,143.0,0.0103,0.0103,163.5,0.0097,0.0097,185.0,0.0093,0.0093,208.0,0.0089,0.0089,232.5,0.0087,0.0087,258.5,0.0085,0.0085,286.0,0.0083,0.0083,331.0,0.0083,0.0083,396.0,0.0083,0.0083,468.5,0.0086,0.0086,549.5,0.0090,0.0090,639.0,0.0095,0.0095,738.0,0.0101,0.0101,847.5,0.0108,0.0108,968.5,0.0114,0.0114,1102.0,0.0118,0.0118,1249.5,0.0122,0.0122,1412.0,0.0126,0.0126,1590.5,0.0130,0.0130,1787.0,0.0134,0.0134,1945.0,0.0137,0.0137,2119.0,0.0140,0.0140,2369.0,0.0144,0.0144,2643.5,0.0148,0.0148,2945.0,0.0152,0.0152,3276.5,0.0156,0.0156},
{-2.0,-1.8,132,9.0,0.1026,0.1026,11.0,0.0821,0.0821,13.5,0.0661,0.0661,16.5,0.0520,0.0520,19.5,0.0432,0.0432,22.5,0.0370,0.0370,26.0,0.0320,0.0320,30.0,0.0280,0.0280,34.5,0.0240,0.0240,40.0,0.0205,0.0205,46.0,0.0179,0.0179,52.5,0.0160,0.0160,60.0,0.0146,0.0146,69.0,0.0133,0.0133,79.0,0.0122,0.0122,90.5,0.0113,0.0113,105.5,0.0104,0.0104,123.5,0.0097,0.0097,143.0,0.0091,0.0091,163.5,0.0086,0.0086,185.0,0.0082,0.0082,208.0,0.0080,0.0080,232.5,0.0077,0.0077,258.5,0.0075,0.0075,286.0,0.0074,0.0074,331.0,0.0073,0.0073,396.0,0.0073,0.0073,468.5,0.0074,0.0074,549.5,0.0077,0.0077,639.0,0.0080,0.0080,738.0,0.0084,0.0084,847.5,0.0089,0.0089,968.5,0.0094,0.0094,1102.0,0.0099,0.0099,1249.5,0.0103,0.0103,1412.0,0.0107,0.0107,1590.5,0.0111,0.0111,1787.0,0.0116,0.0116,1945.0,0.0119,0.0119,2119.0,0.0122,0.0122,2369.0,0.0126,0.0126,2643.5,0.0130,0.0130,2945.0,0.0134,0.0134,3276.5,0.0138,0.0138},
{-1.8,-1.6,132,9.0,0.0977,0.0977,11.0,0.0784,0.0784,13.5,0.0616,0.0616,16.5,0.0513,0.0513,19.5,0.0419,0.0419,22.5,0.0361,0.0361,26.0,0.0314,0.0314,30.0,0.0277,0.0277,34.5,0.0240,0.0240,40.0,0.0207,0.0207,46.0,0.0183,0.0183,52.5,0.0165,0.0165,60.0,0.0152,0.0152,69.0,0.0138,0.0138,79.0,0.0127,0.0127,90.5,0.0118,0.0118,105.5,0.0108,0.0108,123.5,0.0100,0.0100,143.0,0.0094,0.0094,163.5,0.0089,0.0089,185.0,0.0085,0.0085,208.0,0.0081,0.0081,232.5,0.0078,0.0078,258.5,0.0076,0.0076,286.0,0.0074,0.0074,331.0,0.0073,0.0073,396.0,0.0072,0.0072,468.5,0.0073,0.0073,549.5,0.0075,0.0075,639.0,0.0078,0.0078,738.0,0.0082,0.0082,847.5,0.0086,0.0086,968.5,0.0091,0.0091,1102.0,0.0096,0.0096,1249.5,0.0101,0.0101,1412.0,0.0106,0.0106,1590.5,0.0110,0.0110,1787.0,0.0113,0.0113,1945.0,0.0116,0.0116,2119.0,0.0118,0.0118,2369.0,0.0121,0.0121,2643.5,0.0124,0.0124,2945.0,0.0127,0.0127,3276.5,0.0130,0.0130},
{-1.6,-1.4,132,9.0,0.1006,0.1006,11.0,0.0807,0.0807,13.5,0.0642,0.0642,16.5,0.0504,0.0504,19.5,0.0433,0.0433,22.5,0.0369,0.0369,26.0,0.0320,0.0320,30.0,0.0282,0.0282,34.5,0.0243,0.0243,40.0,0.0210,0.0210,46.0,0.0185,0.0185,52.5,0.0167,0.0167,60.0,0.0153,0.0153,69.0,0.0139,0.0139,79.0,0.0128,0.0128,90.5,0.0118,0.0118,105.5,0.0109,0.0109,123.5,0.0101,0.0101,143.0,0.0094,0.0094,163.5,0.0089,0.0089,185.0,0.0085,0.0085,208.0,0.0082,0.0082,232.5,0.0079,0.0079,258.5,0.0076,0.0076,286.0,0.0075,0.0075,331.0,0.0073,0.0073,396.0,0.0072,0.0072,468.5,0.0073,0.0073,549.5,0.0075,0.0075,639.0,0.0077,0.0077,738.0,0.0080,0.0080,847.5,0.0084,0.0084,968.5,0.0088,0.0088,1102.0,0.0092,0.0092,1249.5,0.0097,0.0097,1412.0,0.0102,0.0102,1590.5,0.0106,0.0106,1787.0,0.0110,0.0110,1945.0,0.0112,0.0112,2119.0,0.0114,0.0114,2369.0,0.0116,0.0116,2643.5,0.0119,0.0119,2945.0,0.0121,0.0121,3276.5,0.0124,0.0124},
{-1.4,-1.2,132,9.0,0.1036,0.1036,11.0,0.0827,0.0827,13.5,0.0654,0.0654,16.5,0.0518,0.0518,19.5,0.0428,0.0428,22.5,0.0356,0.0356,26.0,0.0312,0.0312,30.0,0.0276,0.0276,34.5,0.0238,0.0238,40.0,0.0196,0.0196,46.0,0.0169,0.0169,52.5,0.0149,0.0149,60.0,0.0133,0.0133,69.0,0.0119,0.0119,79.0,0.0108,0.0108,90.5,0.0099,0.0099,105.5,0.0091,0.0091,123.5,0.0084,0.0084,143.0,0.0078,0.0078,163.5,0.0074,0.0074,185.0,0.0071,0.0071,208.0,0.0069,0.0069,232.5,0.0067,0.0067,258.5,0.0065,0.0065,286.0,0.0064,0.0064,331.0,0.0063,0.0063,396.0,0.0063,0.0063,468.5,0.0063,0.0063,549.5,0.0065,0.0065,639.0,0.0067,0.0067,738.0,0.0069,0.0069,847.5,0.0072,0.0072,968.5,0.0075,0.0075,1102.0,0.0078,0.0078,1249.5,0.0081,0.0081,1412.0,0.0084,0.0084,1590.5,0.0087,0.0087,1787.0,0.0090,0.0090,1945.0,0.0093,0.0093,2119.0,0.0095,0.0095,2369.0,0.0097,0.0097,2643.5,0.0099,0.0099,2945.0,0.0101,0.0101,3276.5,0.0104,0.0104},
{-1.2,-1.0,132,9.0,0.1030,0.1030,11.0,0.0822,0.0822,13.5,0.0650,0.0650,16.5,0.0516,0.0516,19.5,0.0426,0.0426,22.5,0.0356,0.0356,26.0,0.0312,0.0312,30.0,0.0276,0.0276,34.5,0.0237,0.0237,40.0,0.0194,0.0194,46.0,0.0167,0.0167,52.5,0.0146,0.0146,60.0,0.0130,0.0130,69.0,0.0117,0.0117,79.0,0.0106,0.0106,90.5,0.0097,0.0097,105.5,0.0089,0.0089,123.5,0.0082,0.0082,143.0,0.0077,0.0077,163.5,0.0073,0.0073,185.0,0.0070,0.0070,208.0,0.0068,0.0068,232.5,0.0066,0.0066,258.5,0.0064,0.0064,286.0,0.0064,0.0064,331.0,0.0063,0.0063,396.0,0.0063,0.0063,468.5,0.0063,0.0063,549.5,0.0065,0.0065,639.0,0.0067,0.0067,738.0,0.0069,0.0069,847.5,0.0071,0.0071,968.5,0.0074,0.0074,1102.0,0.0077,0.0077,1249.5,0.0080,0.0080,1412.0,0.0083,0.0083,1590.5,0.0086,0.0086,1787.0,0.0089,0.0089,1945.0,0.0091,0.0091,2119.0,0.0093,0.0093,2369.0,0.0095,0.0095,2643.5,0.0098,0.0098,2945.0,0.0100,0.0100,3276.5,0.0102,0.0102},
{-1.0,-0.8,132,9.0,0.0934,0.0934,11.0,0.0748,0.0748,13.5,0.0595,0.0595,16.5,0.0476,0.0476,19.5,0.0385,0.0385,22.5,0.0339,0.0339,26.0,0.0300,0.0300,30.0,0.0268,0.0268,34.5,0.0223,0.0223,40.0,0.0190,0.0190,46.0,0.0165,0.0165,52.5,0.0146,0.0146,60.0,0.0131,0.0131,69.0,0.0118,0.0118,79.0,0.0108,0.0108,90.5,0.0099,0.0099,105.5,0.0090,0.0090,123.5,0.0083,0.0083,143.0,0.0078,0.0078,163.5,0.0074,0.0074,185.0,0.0071,0.0071,208.0,0.0068,0.0068,232.5,0.0066,0.0066,258.5,0.0065,0.0065,286.0,0.0064,0.0064,331.0,0.0063,0.0063,396.0,0.0063,0.0063,468.5,0.0063,0.0063,549.5,0.0065,0.0065,639.0,0.0067,0.0067,738.0,0.0069,0.0069,847.5,0.0072,0.0072,968.5,0.0074,0.0074,1102.0,0.0077,0.0077,1249.5,0.0080,0.0080,1412.0,0.0083,0.0083,1590.5,0.0087,0.0087,1787.0,0.0090,0.0090,1945.0,0.0092,0.0092,2119.0,0.0094,0.0094,2369.0,0.0096,0.0096,2643.5,0.0098,0.0098,2945.0,0.0101,0.0101,3276.5,0.0103,0.0103},
{-0.8,-0.6,132,9.0,0.0903,0.0903,11.0,0.0724,0.0724,13.5,0.0577,0.0577,16.5,0.0462,0.0462,19.5,0.0378,0.0378,22.5,0.0334,0.0334,26.0,0.0296,0.0296,30.0,0.0256,0.0256,34.5,0.0219,0.0219,40.0,0.0187,0.0187,46.0,0.0162,0.0162,52.5,0.0143,0.0143,60.0,0.0129,0.0129,69.0,0.0116,0.0116,79.0,0.0105,0.0105,90.5,0.0097,0.0097,105.5,0.0088,0.0088,123.5,0.0082,0.0082,143.0,0.0076,0.0076,163.5,0.0073,0.0073,185.0,0.0070,0.0070,208.0,0.0067,0.0067,232.5,0.0065,0.0065,258.5,0.0064,0.0064,286.0,0.0063,0.0063,331.0,0.0062,0.0062,396.0,0.0062,0.0062,468.5,0.0063,0.0063,549.5,0.0065,0.0065,639.0,0.0066,0.0066,738.0,0.0069,0.0069,847.5,0.0071,0.0071,968.5,0.0074,0.0074,1102.0,0.0077,0.0077,1249.5,0.0080,0.0080,1412.0,0.0083,0.0083,1590.5,0.0085,0.0085,1787.0,0.0088,0.0088,1945.0,0.0091,0.0091,2119.0,0.0093,0.0093,2369.0,0.0095,0.0095,2643.5,0.0097,0.0097,2945.0,0.0100,0.0100,3276.5,0.0102,0.0102},
{-0.6,-0.4,132,9.0,0.0924,0.0924,11.0,0.0741,0.0741,13.5,0.0590,0.0590,16.5,0.0473,0.0473,19.5,0.0389,0.0389,22.5,0.0343,0.0343,26.0,0.0304,0.0304,30.0,0.0260,0.0260,34.5,0.0222,0.0222,40.0,0.0189,0.0189,46.0,0.0163,0.0163,52.5,0.0144,0.0144,60.0,0.0129,0.0129,69.0,0.0116,0.0116,79.0,0.0105,0.0105,90.5,0.0097,0.0097,105.5,0.0088,0.0088,123.5,0.0082,0.0082,143.0,0.0076,0.0076,163.5,0.0073,0.0073,185.0,0.0070,0.0070,208.0,0.0067,0.0067,232.5,0.0066,0.0066,258.5,0.0064,0.0064,286.0,0.0063,0.0063,331.0,0.0062,0.0062,396.0,0.0062,0.0062,468.5,0.0063,0.0063,549.5,0.0065,0.0065,639.0,0.0066,0.0066,738.0,0.0069,0.0069,847.5,0.0071,0.0071,968.5,0.0074,0.0074,1102.0,0.0077,0.0077,1249.5,0.0080,0.0080,1412.0,0.0083,0.0083,1590.5,0.0086,0.0086,1787.0,0.0089,0.0089,1945.0,0.0091,0.0091,2119.0,0.0093,0.0093,2369.0,0.0096,0.0096,2643.5,0.0098,0.0098,2945.0,0.0100,0.0100,3276.5,0.0103,0.0103},
{-0.4,-0.2,132,9.0,0.0918,0.0918,11.0,0.0735,0.0735,13.5,0.0586,0.0586,16.5,0.0469,0.0469,19.5,0.0385,0.0385,22.5,0.0339,0.0339,26.0,0.0301,0.0301,30.0,0.0259,0.0259,34.5,0.0221,0.0221,40.0,0.0188,0.0188,46.0,0.0163,0.0163,52.5,0.0144,0.0144,60.0,0.0129,0.0129,69.0,0.0116,0.0116,79.0,0.0105,0.0105,90.5,0.0097,0.0097,105.5,0.0089,0.0089,123.5,0.0082,0.0082,143.0,0.0077,0.0077,163.5,0.0073,0.0073,185.0,0.0070,0.0070,208.0,0.0067,0.0067,232.5,0.0066,0.0066,258.5,0.0064,0.0064,286.0,0.0063,0.0063,331.0,0.0062,0.0062,396.0,0.0062,0.0062,468.5,0.0063,0.0063,549.5,0.0065,0.0065,639.0,0.0066,0.0066,738.0,0.0069,0.0069,847.5,0.0071,0.0071,968.5,0.0074,0.0074,1102.0,0.0077,0.0077,1249.5,0.0080,0.0080,1412.0,0.0083,0.0083,1590.5,0.0086,0.0086,1787.0,0.0089,0.0089,1945.0,0.0091,0.0091,2119.0,0.0093,0.0093,2369.0,0.0095,0.0095,2643.5,0.0098,0.0098,2945.0,0.0100,0.0100,3276.5,0.0102,0.0102},
{-0.2,0.0,132,9.0,0.0926,0.0926,11.0,0.0742,0.0742,13.5,0.0591,0.0591,16.5,0.0473,0.0473,19.5,0.0388,0.0388,22.5,0.0342,0.0342,26.0,0.0303,0.0303,30.0,0.0260,0.0260,34.5,0.0222,0.0222,40.0,0.0189,0.0189,46.0,0.0163,0.0163,52.5,0.0144,0.0144,60.0,0.0129,0.0129,69.0,0.0116,0.0116,79.0,0.0105,0.0105,90.5,0.0096,0.0096,105.5,0.0088,0.0088,123.5,0.0081,0.0081,143.0,0.0076,0.0076,163.5,0.0072,0.0072,185.0,0.0070,0.0070,208.0,0.0067,0.0067,232.5,0.0065,0.0065,258.5,0.0064,0.0064,286.0,0.0063,0.0063,331.0,0.0062,0.0062,396.0,0.0062,0.0062,468.5,0.0063,0.0063,549.5,0.0065,0.0065,639.0,0.0066,0.0066,738.0,0.0069,0.0069,847.5,0.0071,0.0071,968.5,0.0074,0.0074,1102.0,0.0077,0.0077,1249.5,0.0080,0.0080,1412.0,0.0083,0.0083,1590.5,0.0086,0.0086,1787.0,0.0089,0.0089,1945.0,0.0091,0.0091,2119.0,0.0093,0.0093,2369.0,0.0095,0.0095,2643.5,0.0098,0.0098,2945.0,0.0100,0.0100,3276.5,0.0102,0.0102},
{0.0,0.2,132,9.0,0.0914,0.0914,11.0,0.0733,0.0733,13.5,0.0584,0.0584,16.5,0.0468,0.0468,19.5,0.0383,0.0383,22.5,0.0338,0.0338,26.0,0.0299,0.0299,30.0,0.0258,0.0258,34.5,0.0221,0.0221,40.0,0.0188,0.0188,46.0,0.0163,0.0163,52.5,0.0144,0.0144,60.0,0.0129,0.0129,69.0,0.0116,0.0116,79.0,0.0105,0.0105,90.5,0.0096,0.0096,105.5,0.0088,0.0088,123.5,0.0082,0.0082,143.0,0.0076,0.0076,163.5,0.0072,0.0072,185.0,0.0070,0.0070,208.0,0.0067,0.0067,232.5,0.0065,0.0065,258.5,0.0064,0.0064,286.0,0.0063,0.0063,331.0,0.0062,0.0062,396.0,0.0062,0.0062,468.5,0.0063,0.0063,549.5,0.0065,0.0065,639.0,0.0066,0.0066,738.0,0.0069,0.0069,847.5,0.0071,0.0071,968.5,0.0074,0.0074,1102.0,0.0077,0.0077,1249.5,0.0080,0.0080,1412.0,0.0083,0.0083,1590.5,0.0086,0.0086,1787.0,0.0089,0.0089,1945.0,0.0091,0.0091,2119.0,0.0093,0.0093,2369.0,0.0095,0.0095,2643.5,0.0097,0.0097,2945.0,0.0100,0.0100,3276.5,0.0102,0.0102},
{0.2,0.4,132,9.0,0.0919,0.0919,11.0,0.0737,0.0737,13.5,0.0587,0.0587,16.5,0.0470,0.0470,19.5,0.0386,0.0386,22.5,0.0340,0.0340,26.0,0.0302,0.0302,30.0,0.0259,0.0259,34.5,0.0221,0.0221,40.0,0.0189,0.0189,46.0,0.0163,0.0163,52.5,0.0144,0.0144,60.0,0.0129,0.0129,69.0,0.0116,0.0116,79.0,0.0106,0.0106,90.5,0.0097,0.0097,105.5,0.0089,0.0089,123.5,0.0082,0.0082,143.0,0.0077,0.0077,163.5,0.0073,0.0073,185.0,0.0070,0.0070,208.0,0.0067,0.0067,232.5,0.0066,0.0066,258.5,0.0064,0.0064,286.0,0.0063,0.0063,331.0,0.0062,0.0062,396.0,0.0062,0.0062,468.5,0.0063,0.0063,549.5,0.0065,0.0065,639.0,0.0066,0.0066,738.0,0.0069,0.0069,847.5,0.0071,0.0071,968.5,0.0074,0.0074,1102.0,0.0077,0.0077,1249.5,0.0080,0.0080,1412.0,0.0083,0.0083,1590.5,0.0086,0.0086,1787.0,0.0089,0.0089,1945.0,0.0091,0.0091,2119.0,0.0093,0.0093,2369.0,0.0095,0.0095,2643.5,0.0098,0.0098,2945.0,0.0100,0.0100,3276.5,0.0103,0.0103},
{0.4,0.6,132,9.0,0.0895,0.0895,11.0,0.0717,0.0717,13.5,0.0571,0.0571,16.5,0.0458,0.0458,19.5,0.0375,0.0375,22.5,0.0331,0.0331,26.0,0.0294,0.0294,30.0,0.0255,0.0255,34.5,0.0218,0.0218,40.0,0.0186,0.0186,46.0,0.0162,0.0162,52.5,0.0143,0.0143,60.0,0.0128,0.0128,69.0,0.0116,0.0116,79.0,0.0105,0.0105,90.5,0.0096,0.0096,105.5,0.0088,0.0088,123.5,0.0082,0.0082,143.0,0.0076,0.0076,163.5,0.0073,0.0073,185.0,0.0070,0.0070,208.0,0.0067,0.0067,232.5,0.0065,0.0065,258.5,0.0064,0.0064,286.0,0.0063,0.0063,331.0,0.0062,0.0062,396.0,0.0062,0.0062,468.5,0.0063,0.0063,549.5,0.0065,0.0065,639.0,0.0066,0.0066,738.0,0.0069,0.0069,847.5,0.0071,0.0071,968.5,0.0074,0.0074,1102.0,0.0077,0.0077,1249.5,0.0080,0.0080,1412.0,0.0082,0.0082,1590.5,0.0085,0.0085,1787.0,0.0088,0.0088,1945.0,0.0091,0.0091,2119.0,0.0092,0.0092,2369.0,0.0095,0.0095,2643.5,0.0097,0.0097,2945.0,0.0099,0.0099,3276.5,0.0102,0.0102},
{0.6,0.8,132,9.0,0.0910,0.0910,11.0,0.0729,0.0729,13.5,0.0581,0.0581,16.5,0.0466,0.0466,19.5,0.0382,0.0382,22.5,0.0337,0.0337,26.0,0.0299,0.0299,30.0,0.0257,0.0257,34.5,0.0220,0.0220,40.0,0.0188,0.0188,46.0,0.0163,0.0163,52.5,0.0144,0.0144,60.0,0.0129,0.0129,69.0,0.0116,0.0116,79.0,0.0105,0.0105,90.5,0.0097,0.0097,105.5,0.0089,0.0089,123.5,0.0082,0.0082,143.0,0.0077,0.0077,163.5,0.0073,0.0073,185.0,0.0070,0.0070,208.0,0.0067,0.0067,232.5,0.0066,0.0066,258.5,0.0064,0.0064,286.0,0.0063,0.0063,331.0,0.0062,0.0062,396.0,0.0062,0.0062,468.5,0.0063,0.0063,549.5,0.0065,0.0065,639.0,0.0066,0.0066,738.0,0.0069,0.0069,847.5,0.0071,0.0071,968.5,0.0074,0.0074,1102.0,0.0077,0.0077,1249.5,0.0080,0.0080,1412.0,0.0083,0.0083,1590.5,0.0086,0.0086,1787.0,0.0089,0.0089,1945.0,0.0091,0.0091,2119.0,0.0093,0.0093,2369.0,0.0095,0.0095,2643.5,0.0098,0.0098,2945.0,0.0100,0.0100,3276.5,0.0102,0.0102},
{0.8,1.0,132,9.0,0.0942,0.0942,11.0,0.0755,0.0755,13.5,0.0601,0.0601,16.5,0.0481,0.0481,19.5,0.0393,0.0393,22.5,0.0346,0.0346,26.0,0.0306,0.0306,30.0,0.0263,0.0263,34.5,0.0225,0.0225,40.0,0.0192,0.0192,46.0,0.0166,0.0166,52.5,0.0147,0.0147,60.0,0.0132,0.0132,69.0,0.0118,0.0118,79.0,0.0108,0.0108,90.5,0.0099,0.0099,105.5,0.0091,0.0091,123.5,0.0084,0.0084,143.0,0.0078,0.0078,163.5,0.0074,0.0074,185.0,0.0071,0.0071,208.0,0.0068,0.0068,232.5,0.0066,0.0066,258.5,0.0065,0.0065,286.0,0.0064,0.0064,331.0,0.0063,0.0063,396.0,0.0063,0.0063,468.5,0.0063,0.0063,549.5,0.0065,0.0065,639.0,0.0067,0.0067,738.0,0.0069,0.0069,847.5,0.0072,0.0072,968.5,0.0074,0.0074,1102.0,0.0077,0.0077,1249.5,0.0081,0.0081,1412.0,0.0084,0.0084,1590.5,0.0087,0.0087,1787.0,0.0090,0.0090,1945.0,0.0092,0.0092,2119.0,0.0094,0.0094,2369.0,0.0097,0.0097,2643.5,0.0099,0.0099,2945.0,0.0102,0.0102,3276.5,0.0104,0.0104},
{1.0,1.2,132,9.0,0.1010,0.1010,11.0,0.0807,0.0807,13.5,0.0638,0.0638,16.5,0.0507,0.0507,19.5,0.0419,0.0419,22.5,0.0350,0.0350,26.0,0.0307,0.0307,30.0,0.0272,0.0272,34.5,0.0235,0.0235,40.0,0.0193,0.0193,46.0,0.0166,0.0166,52.5,0.0145,0.0145,60.0,0.0130,0.0130,69.0,0.0116,0.0116,79.0,0.0105,0.0105,90.5,0.0096,0.0096,105.5,0.0088,0.0088,123.5,0.0082,0.0082,143.0,0.0077,0.0077,163.5,0.0073,0.0073,185.0,0.0070,0.0070,208.0,0.0068,0.0068,232.5,0.0066,0.0066,258.5,0.0064,0.0064,286.0,0.0063,0.0063,331.0,0.0063,0.0063,396.0,0.0063,0.0063,468.5,0.0063,0.0063,549.5,0.0065,0.0065,639.0,0.0067,0.0067,738.0,0.0069,0.0069,847.5,0.0071,0.0071,968.5,0.0074,0.0074,1102.0,0.0077,0.0077,1249.5,0.0080,0.0080,1412.0,0.0083,0.0083,1590.5,0.0086,0.0086,1787.0,0.0089,0.0089,1945.0,0.0091,0.0091,2119.0,0.0093,0.0093,2369.0,0.0095,0.0095,2643.5,0.0097,0.0097,2945.0,0.0099,0.0099,3276.5,0.0102,0.0102},
{1.2,1.4,132,9.0,0.1015,0.1015,11.0,0.0809,0.0809,13.5,0.0639,0.0639,16.5,0.0506,0.0506,19.5,0.0418,0.0418,22.5,0.0357,0.0357,26.0,0.0301,0.0301,30.0,0.0267,0.0267,34.5,0.0230,0.0230,40.0,0.0197,0.0197,46.0,0.0165,0.0165,52.5,0.0145,0.0145,60.0,0.0130,0.0130,69.0,0.0116,0.0116,79.0,0.0106,0.0106,90.5,0.0097,0.0097,105.5,0.0089,0.0089,123.5,0.0082,0.0082,143.0,0.0077,0.0077,163.5,0.0073,0.0073,185.0,0.0070,0.0070,208.0,0.0068,0.0068,232.5,0.0066,0.0066,258.5,0.0064,0.0064,286.0,0.0063,0.0063,331.0,0.0063,0.0063,396.0,0.0063,0.0063,468.5,0.0063,0.0063,549.5,0.0065,0.0065,639.0,0.0067,0.0067,738.0,0.0069,0.0069,847.5,0.0071,0.0071,968.5,0.0074,0.0074,1102.0,0.0077,0.0077,1249.5,0.0080,0.0080,1412.0,0.0083,0.0083,1590.5,0.0086,0.0086,1787.0,0.0088,0.0088,1945.0,0.0091,0.0091,2119.0,0.0092,0.0092,2369.0,0.0095,0.0095,2643.5,0.0097,0.0097,2945.0,0.0099,0.0099,3276.5,0.0101,0.0101},
{1.4,1.6,132,9.0,0.0979,0.0979,11.0,0.0785,0.0785,13.5,0.0626,0.0626,16.5,0.0502,0.0502,19.5,0.0419,0.0419,22.5,0.0370,0.0370,26.0,0.0316,0.0316,30.0,0.0280,0.0280,34.5,0.0243,0.0243,40.0,0.0211,0.0211,46.0,0.0187,0.0187,52.5,0.0170,0.0170,60.0,0.0157,0.0157,69.0,0.0144,0.0144,79.0,0.0132,0.0132,90.5,0.0122,0.0122,105.5,0.0112,0.0112,123.5,0.0104,0.0104,143.0,0.0097,0.0097,163.5,0.0091,0.0091,185.0,0.0087,0.0087,208.0,0.0083,0.0083,232.5,0.0080,0.0080,258.5,0.0077,0.0077,286.0,0.0075,0.0075,331.0,0.0073,0.0073,396.0,0.0072,0.0072,468.5,0.0073,0.0073,549.5,0.0075,0.0075,639.0,0.0077,0.0077,738.0,0.0081,0.0081,847.5,0.0085,0.0085,968.5,0.0089,0.0089,1102.0,0.0094,0.0094,1249.5,0.0099,0.0099,1412.0,0.0104,0.0104,1590.5,0.0109,0.0109,1787.0,0.0113,0.0113,1945.0,0.0115,0.0115,2119.0,0.0117,0.0117,2369.0,0.0119,0.0119,2643.5,0.0121,0.0121,2945.0,0.0123,0.0123,3276.5,0.0125,0.0125},
{1.6,1.8,132,9.0,0.0931,0.0931,11.0,0.0746,0.0746,13.5,0.0595,0.0595,16.5,0.0480,0.0480,19.5,0.0399,0.0399,22.5,0.0345,0.0345,26.0,0.0301,0.0301,30.0,0.0267,0.0267,34.5,0.0230,0.0230,40.0,0.0199,0.0199,46.0,0.0175,0.0175,52.5,0.0158,0.0158,60.0,0.0144,0.0144,69.0,0.0132,0.0132,79.0,0.0121,0.0121,90.5,0.0112,0.0112,105.5,0.0104,0.0104,123.5,0.0097,0.0097,143.0,0.0091,0.0091,163.5,0.0086,0.0086,185.0,0.0083,0.0083,208.0,0.0080,0.0080,232.5,0.0077,0.0077,258.5,0.0075,0.0075,286.0,0.0074,0.0074,331.0,0.0073,0.0073,396.0,0.0072,0.0072,468.5,0.0073,0.0073,549.5,0.0075,0.0075,639.0,0.0078,0.0078,738.0,0.0081,0.0081,847.5,0.0084,0.0084,968.5,0.0088,0.0088,1102.0,0.0092,0.0092,1249.5,0.0096,0.0096,1412.0,0.0101,0.0101,1590.5,0.0104,0.0104,1787.0,0.0107,0.0107,1945.0,0.0110,0.0110,2119.0,0.0112,0.0112,2369.0,0.0115,0.0115,2643.5,0.0118,0.0118,2945.0,0.0120,0.0120,3276.5,0.0123,0.0123},
{1.8,2.0,132,9.0,0.0977,0.0977,11.0,0.0783,0.0783,13.5,0.0621,0.0621,16.5,0.0497,0.0497,19.5,0.0414,0.0414,22.5,0.0356,0.0356,26.0,0.0309,0.0309,30.0,0.0272,0.0272,34.5,0.0234,0.0234,40.0,0.0201,0.0201,46.0,0.0176,0.0176,52.5,0.0158,0.0158,60.0,0.0144,0.0144,69.0,0.0131,0.0131,79.0,0.0120,0.0120,90.5,0.0111,0.0111,105.5,0.0103,0.0103,123.5,0.0096,0.0096,143.0,0.0090,0.0090,163.5,0.0086,0.0086,185.0,0.0082,0.0082,208.0,0.0079,0.0079,232.5,0.0077,0.0077,258.5,0.0075,0.0075,286.0,0.0074,0.0074,331.0,0.0073,0.0073,396.0,0.0073,0.0073,468.5,0.0074,0.0074,549.5,0.0077,0.0077,639.0,0.0080,0.0080,738.0,0.0083,0.0083,847.5,0.0088,0.0088,968.5,0.0092,0.0092,1102.0,0.0097,0.0097,1249.5,0.0101,0.0101,1412.0,0.0105,0.0105,1590.5,0.0109,0.0109,1787.0,0.0113,0.0113,1945.0,0.0115,0.0115,2119.0,0.0118,0.0118,2369.0,0.0122,0.0122,2643.5,0.0125,0.0125,2945.0,0.0129,0.0129,3276.5,0.0133,0.0133},
{2.0,2.2,132,9.0,0.1041,0.1041,11.0,0.0831,0.0831,13.5,0.0651,0.0651,16.5,0.0536,0.0536,19.5,0.0430,0.0430,22.5,0.0368,0.0368,26.0,0.0317,0.0317,30.0,0.0279,0.0279,34.5,0.0240,0.0240,40.0,0.0206,0.0206,46.0,0.0181,0.0181,52.5,0.0163,0.0163,60.0,0.0149,0.0149,69.0,0.0136,0.0136,79.0,0.0126,0.0126,90.5,0.0117,0.0117,105.5,0.0109,0.0109,123.5,0.0102,0.0102,143.0,0.0097,0.0097,163.5,0.0093,0.0093,185.0,0.0090,0.0090,208.0,0.0087,0.0087,232.5,0.0085,0.0085,258.5,0.0084,0.0084,286.0,0.0083,0.0083,331.0,0.0082,0.0082,396.0,0.0082,0.0082,468.5,0.0084,0.0084,549.5,0.0087,0.0087,639.0,0.0090,0.0090,738.0,0.0094,0.0094,847.5,0.0098,0.0098,968.5,0.0103,0.0103,1102.0,0.0106,0.0106,1249.5,0.0110,0.0110,1412.0,0.0113,0.0113,1590.5,0.0117,0.0117,1787.0,0.0121,0.0121,1945.0,0.0123,0.0123,2119.0,0.0126,0.0126,2369.0,0.0129,0.0129,2643.5,0.0133,0.0133,2945.0,0.0136,0.0136,3276.5,0.0139,0.0139},
{2.2,2.4,132,9.0,0.1020,0.1020,11.0,0.0810,0.0810,13.5,0.0628,0.0628,16.5,0.0517,0.0517,19.5,0.0420,0.0420,22.5,0.0361,0.0361,26.0,0.0313,0.0313,30.0,0.0277,0.0277,34.5,0.0240,0.0240,40.0,0.0209,0.0209,46.0,0.0186,0.0186,52.5,0.0169,0.0169,60.0,0.0157,0.0157,69.0,0.0145,0.0145,79.0,0.0134,0.0134,90.5,0.0125,0.0125,105.5,0.0116,0.0116,123.5,0.0108,0.0108,143.0,0.0101,0.0101,163.5,0.0096,0.0096,185.0,0.0092,0.0092,208.0,0.0089,0.0089,232.5,0.0087,0.0087,258.5,0.0085,0.0085,286.0,0.0085,0.0085,331.0,0.0084,0.0084,396.0,0.0086,0.0086,468.5,0.0089,0.0089,549.5,0.0093,0.0093,639.0,0.0098,0.0098,738.0,0.0103,0.0103,847.5,0.0108,0.0108,968.5,0.0111,0.0111,1102.0,0.0114,0.0114,1249.5,0.0118,0.0118,1412.0,0.0121,0.0121,1590.5,0.0125,0.0125,1787.0,0.0129,0.0129,1945.0,0.0131,0.0131,2119.0,0.0134,0.0134,2369.0,0.0137,0.0137,2643.5,0.0141,0.0141,2945.0,0.0144,0.0144,3276.5,0.0147,0.0147}}; 

  double correction = 1;
  if((strcmp(mode,"pPb5")==0 || strcmp(mode,"pp5")==0 || strcmp(mode,"Pbp5")==0 || strcmp(mode,"pp2")==0) && isRelative == false)
  {
    for(int i = 0; i<18; i++)
    {
      if(eta>syst5TeV[i][0] && eta<=syst5TeV[i][1])
      {
        for(int j = 3; j<117; j=j+3)
        {
          if(jetPt>syst5TeV[i][j] && jetPt<=syst5TeV[i][j+3]) return jetPt*TMath::Power(0.04*0.04+syst5TeV[i][j+1]*syst5TeV[i][j+1]+TMath::Power(getJEC_L2L3res("pp7",jetPt)/jetPt,2),0.5); 
        }
      }
    }
  }

  if(strcmp(mode,"pp7")==0 && isRelative == false)
  {
    for(int i = 0; i<24; i++)
    {
      if(eta>syst7TeV[i][0] && eta<=syst7TeV[i][1])
      {
        for(int j = 3; j<132; j=j+3)
        {
          if(jetPt>syst7TeV[i][j] && jetPt<=syst7TeV[i][j+3]) return jetPt*TMath::Power(0.04*0.04+syst7TeV[i][j+1]*syst7TeV[i][j+1]+TMath::Power(getJEC_L2L3res("pp7",jetPt)/jetPt,2),0.5); 
        }
      }
    }
  }

  if(isRelative == true)
  {
    double error7 = 0;
    double error5 = 0;
    for(int i = 0; i<24; i++)
    {
      if(eta>syst7TeV[i][0] && eta<=syst7TeV[i][1])
      {
        for(int j = 3; j<132; j=j+3)
        {
          if(jetPt>syst7TeV[i][j] && jetPt<=syst7TeV[i][j+3]) error7 = syst7TeV[i][j+1]*syst7TeV[i][j+1];
        }
      }
    }
    for(int i = 0; i<18; i++)
    {
      if(eta>syst5TeV[i][0] && eta<=syst5TeV[i][1])
      {
        for(int j = 3; j<117; j=j+3)
        {
          if(jetPt>syst5TeV[i][j] && jetPt<=syst5TeV[i][j+3]) error5 = syst5TeV[i][j+1]*syst5TeV[i][j+1];
        }
      }
    }
    return jetPt*TMath::Power(TMath::Abs(error7 - error5)+TMath::Power(getJEC_L2L3res("pp7",jetPt)/jetPt,2),0.5);
  }
}
