// Hydroinfo_MUSIC.h is a part of the MARTINI event generator.
// Copyright (C) 2009 Bjoern Schenke.
// MARTINI is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// This file contains routines to read in hydro data from files and functions
// that return interpolated data at a given space-time point

#ifndef SRC_HYDROINFO_MUSIC_H_
#define SRC_HYDROINFO_MUSIC_H_

#include <vector>
#include <string>
#include "./Hydroinfo_h5.h"

struct fluidCell_2D {
    double temperature;
    double vx, vy;
    // the shear stress tensor are already divided by e+P
    double pi00, pi01, pi02;
    double pi11, pi12;
    double pi22;
    double pi33;
    double bulkPi;
};

struct fluidCell_3D {
    double temperature;
    double vx, vy, vz;
    // the shear stress tensor are already divided by e+P
    double pi00, pi01, pi02, pi03;
    double pi11, pi12, pi13;
    double pi22, pi23;
    double pi33;
    double bulkPi;
};

struct fluidCell_3D_new {
    int itau, ix, iy, ieta;
    double temperature;
    double ux, uy, ueta;
    // the shear stress tensor are already divided by e+P
    double pi11, pi12, pi13;
    double pi22, pi23;
    double bulkPi;
};

class Hydroinfo_MUSIC {
 private:
    double hbarC;
    double hydroTau0;       // tau_0 in the hydro data files
    double hydroTauMax;     // tau_max in the hydro data files
    double hydroDtau;       // step dtau in fm/c in the hydro data files
    double hydroXmax;       // maximum x in fm in the hydro data files
                            // [-xmax, +xmax] for both x and y
    double hydro_eta_max;       // maximum z in fm in the hydro data files
                            // [-zmax, +zmax] for 3D hydro
    double hydroDx;         // step dx in fm in the hydro data files
    double hydroDeta;         // step dz in fm in the hydro data files in
                            // the z-direction for 3D hydro

    int nskip_tau, nskip_x, nskip_eta;

    int hydroWhichHydro;    // choose a hydro evolution model to use
    int use_tau_eta_coordinate;

    bool boost_invariant;

    int itaumax, ixmax, ietamax;
    int turn_on_shear;
    int turn_on_bulk;
    int turn_on_rhob;
    int turn_on_diff;

    std::vector<fluidCell_2D> *lattice_2D;  // array to store hydro information
    std::vector<fluidCell_3D> *lattice_3D;  // array to store hydro information
    std::vector<fluidCell_3D_new> *lattice_3D_new;

 public:
    Hydroinfo_MUSIC();       // constructor
    ~Hydroinfo_MUSIC();      // destructor

    double get_hydro_tau_max() {return(hydroTauMax);}
    double get_hydro_tau0() {return(hydroTau0);}
    double get_hydro_dtau() {return(hydroDtau);}
    double get_hydro_dx() {return(hydroDx);}
    double get_hydro_deta() {return(hydroDeta);}
    double get_hydro_eta_max() {return(hydro_eta_max);}
    double get_hydro_x_max() {return(hydroXmax);}
    int get_hydro_Nskip_tau() {return(nskip_tau);}
    int get_hydro_Nskip_x() {return(nskip_x);}
    int get_hydro_Nskip_eta() {return(nskip_eta);}
    int get_number_of_fluid_cells_3d() {return(lattice_3D_new->size());}

    void readHydroData(int whichHydro, int nskip_tau_in);

    void getHydroValues(double x, double y, double z, double t,
                        fluidCell *info);
    void get_hydro_cell_info_3d(int cell_id, fluidCell_3D_new *info);
    void output_temperature_evolution(std::string filename_base);
    void update_grid_info(double tau0, double tau_max, double dtau,
                          double x_max, double dx, double z_max, double dz);
};

#endif  // SRC_HYDROINFO_MUSIC_H_

