// CURRENT WORKING AND CONFIRMED WITH TABLE

/*
******************************************************************** 
 THIS PROGRAM CALCULATES INSTANTANEOUS VELOCITY, DISTANCE OF FALL,
 DRAG AREA, AND OPENING SHOCK FORCE OF A PARACHUTE DEPLOYED IN
 ANY DIRECTION

 THE PROGRAM OPERATES IN TWO MODES:

 MODE 1 - CALCULATES THE INFLATION TIME AND PERFORMANCE PROFILES FOR
          SOLID-CLOTH PARACHUTES (TO INPUT AS INITIAL ESTIMATE)
          (IDPT=1)

 MODE 2 - CALCULATES THE PERFORMANCE PROFILES FOR VARIOUS TYPES OF
           PARACHUTES (J). INFLATION TIME IS REQUIRED AS INPUT
           (IGPT=2)
******************************************************************** 

 INPUT NEEDED FOR BOTH MODES:
       ALT     - ALTITUDE. (FT) NOT USED IN ANY CALCULATIONS.
       RHO     - AIR DENSITY AT GIVEN ALTITUDE. (SLUGS/FT3)
        VS     - VELOCITY AT SUSPENSION LINE STRETCH. (FT/SEC)
      CDS0     - DESIGN DRAG AREA. (FT2)
        TO     - I0PT=1 INITIAL GUESS FOR INFLATION REF TIME (SEC)
                 I0PT=2 ACTUAL INFLATION REFERENCE TIME (SEC)
         W       - WEIGHT (LBS)
         J       - =6 FOR FLAT CIRCULAR PARACHUTE.
                   =1 FOR RIBBON TYPE OF PARACHUTE.
       TAU     - INITIAL DRAG-AREA RATIO.
   ALPHA(O)    - INITIAL DEPLOYMENT ANGLE. (DEG) POSITIVE DOWNWARD

 ADDITIONAL INPUT NEEDED FOR IOPT = 1 ONLY

       AMO      - STEADY-STATE MOUTH AREA. (FT2)
       ASO      - CANOPY DESIGN SURFACE AREA. (FT2)
         K      - CLOTH PERMEABILITY CONSTANT
        CP      - PRESSURE COEFFICIENT
         N      - CLOTH PERMEABILITY EXPONENT I
        VO      - GEOMETRIC VOLUME. (FT3)
*/

// select IOPT=1, i.e. enter 1

// testing input for ALT, RHO, VS, CDS0, T0, W, J, TAU, ALPHA(O)
// 3000 0.0021753 325.3 725.58 0.751 200 6 0 90

// testing input for AMO, ASO, K, CP, N, VO
// 399.53 962.1 1.46 1.70 0.500 4690.3

#include <stdio.h>
#include <math.h>

int main() {
  float N, ALT, RHO, VS, CDS0, T0, W, J, TAU, ALPHA0;
  float AMO, ASO, XK, CP, VO, DT, G, S, X, CDS, FS, F, VOL;
  int IOPT, IPASS, LCOUNT, IBYPASS;
  float V, ALPHA, T, XM, TFAC, DVX, DVY, VX, VY, DVOL;
  float R, DS, DPRINT, TOLD, TPREV, TOVT0, FOLD;
  const int T0DEN = 100000;
  const int MAX_ITERATIONS = 50;
  printf("INPUT IOPT\n");
  scanf("%d", &IOPT);
  printf("INPUT ALT, RHO, VS, CDS0, T0, W, J, TAU, ALPHA(O)\n");
  scanf("%f %f %f %f %f %f %f %f %f", &ALT, &RHO, &VS, &CDS0, &T0, &W, &J, &TAU, &ALPHA0);
  if (IOPT == 2) goto label3;
  printf("INPUT AMO, ASO, K, CP, N, VO\n");
  scanf("%f %f %f %f %f %f", &AMO, &ASO, &XK, &CP, &N, &VO);
  
label3:
  DT = T0 / T0DEN;
  G = 32.2;
  S = 0.0;
  X = TAU;
  CDS = TAU * CDS0;
  FS = 0.5 * RHO * pow(VS, 2) * CDS0;
  F = TAU * FS;
  VOL = 0.0;
  IPASS = 0;
  DT = 10 * DT;
  if (IOPT == 2) goto label8;
label7:
  V = VS;
  ALPHA = ALPHA0;
  VOL = 0.0;
  T = 0.0;
  XM = (2 * W) / (RHO * G * CDS0 * VS * T0);
label6:
  TFAC = (1 - TAU) * pow((T / T0), J) + TAU;
  DVX = -pow(V, 2) * cos(ALPHA) * TFAC / (XM * VS * T0) * DT;
  DVY = (G - pow(V, 2) / (XM * VS * T0) * TFAC * sin(ALPHA)) * DT;
  VX = V * cos(ALPHA);
  VY = V * sin(ALPHA);
  VX = VX + DVX;
  VY = VY + DVY;
  V = sqrt(pow(VX, 2) + pow(VY, 2));
  DVOL = (V * AMO * pow((T / T0), J) - ASO * pow((T / T0), J) * XK * pow((CP * RHO / 2), N) * pow(V, (2 * N))) * DT;
  VOL = VOL + DVOL;
  if (VX != 0) ALPHA = atan2(VY, VX);
  T = T + DT;
  if (T >= T0) goto label4;
  goto label6;
label4:
  if (VOL > (VO - 10) && VOL < (VO + 10)) goto label8;
  T0 = T0 * (VO / VOL);
  if (IPASS > MAX_ITERATIONS) {
    printf("VOLUME ITERATION FAILED AFTER 50 PASSES");
    return 0;
  }
  IPASS = IPASS + 1;
  goto label7;
label8:
  XM = (2 * W) / (RHO * G * CDS0 * VS * T0);
  T = 0.0;
  V = VS;
  ALPHA = ALPHA0;
  R = 0.0;
  S = 0.0;
  DS = 0.0;
  DPRINT = T0 / 50;
  DT = DT / 10.0;
  printf("0\n");
  printf("\n");
  printf("DEPLOYMENT CONDITIONS                 SYSTEM PARAMETERS\n");
  printf(" ALTITUDE = %7.0f FT               STEADY STATE DRAG AREA CDS0 = %8.2f FT2\n", ALT, CDS0);
  printf(" DENSITY = %10.7f SLUGS/FT3        WEIGHT W = %6.1f LBS\n", RHO, W);
  printf(" VELOCITY VS = %6.1f FT/SEC        INFLATION TIME TO = %7.3f SEC\n", VS, T0);
  printf(" J = %2.0f                           STEADY STATE DRAG FORCE FS = %9.1f LBS\n", J, FS);
  printf(" TAU = %6.3f                        M = %8.5f\n", TAU, XM);
  printf(" ALPHA0 = %6.2f DEG\n", ALPHA0);
  if (IOPT == 1) printf("N = %6.3f\n", N);
  if (IOPT == 1) printf("AMO = %8.2f FT2\nASO = %8.2f FT2\nK = %6.2f\nVO GEOM = %9.2f FT3\nC.P. = %6.2f\n", AMO, ASO, XK, VO, CP);
  printf("\n");
  printf("TIME         VELOCITY        ALPHA       RANGE        S         DISTANCE        SHOCK                 F\n");
  printf("SEC          FT/SEC          DEG         FT          FT          FT             FACTOR                LBS\n");
  LCOUNT = 11;
  F = 0;
  IBYPASS = 0;
label35:
  if (T / T0 > 1.001 && IBYPASS != 0) goto label5;
  if (LCOUNT < 54) goto label33;
  printf("1\n");
  printf("\n");
  printf("TIME         VELOCITY        ALPHA       RANGE        S         DISTANCE        SHOCK                 F\n");
  printf("SEC          FT/SEC          DEG         FT          FT          FT             FACTOR                LBS\n");
  LCOUNT = 3;
label33:
  LCOUNT = LCOUNT + 1;
  printf("%5.3f   %10.2f    %10.2f  %9.1f      %11.2f %11.2f      %13.3e   %11.1f\n", T, V, ALPHA, R, S, DS, X, F);
  TOLD = T + DPRINT;
  if (DT > DPRINT) TOLD = T + DT;
label40:
  TPREV = T;
  T = T + DT;
  if (T > TOLD) T = TOLD;
  TOVT0 = (1.0 - TAU) * pow((T / T0), J) + TAU;
  CDS = CDS0 * TOVT0;
  DVX = -pow(V, 2) * cos(ALPHA) * TOVT0 / (XM * VS * T0) * DT;
  DVY = (G - pow(V, 2) * TOVT0 * sin(ALPHA) / (XM * VS * T0)) * DT;
  VX = V * cos(ALPHA);
  VY = V * sin(ALPHA);
  VX = VX + DVX;
  VY = VY + DVY;
  V = sqrt(pow(VX, 2) + pow(VY, 2));
  if (VX != 0) ALPHA = atan2(VY, VX);
  R = R + VX * DT;
  S = S + VY * DT;
  DS = DS + V * DT;
  X = pow((V / VS), 2) * CDS / CDS0;
  FOLD = F;
  F = X * FS;
  if (IBYPASS == 1) goto label99;
  if (T - TPREV < DT) goto label99;
  if (F >= FOLD) goto label99;
  IBYPASS = 1;
  printf("%5.3f   %10.2f    %10.2f  %9.1f      %11.2f %11.2f      %13.3e   %11.1f MAX FORCE\n", T, V, ALPHA, R, S, DS, X, F);
  LCOUNT = LCOUNT + 1;
label99:
  if (T < TOLD) goto label40;
  goto label35;
label5:
  return 0;
}


