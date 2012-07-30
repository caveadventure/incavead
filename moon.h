#ifndef __MOON_H
#define __MOON_H

#include <math.h>
#include <time.h>
#include <string>

#include "serialize.h"

namespace constants {

// JDN stands for Julian Day Number
// Angles here are in degrees

// 1980 January 0.0 in JDN
double epoch = 2444239.0;

// Ecliptic longitude of the Sun at epoch 1980.0
double ecliptic_longitude_epoch = 278.833540;

// Ecliptic longitude of the Sun at perigee
double ecliptic_longitude_perigee = 282.596403;

// Eccentricity of Earth's orbit
double eccentricity = 0.016718;

// Semi-major axis of Earth's orbit, in kilometers
double sun_smaxis = 1.49585e8;
  
// Sun's angular size, in degrees, at semi-major axis distance
double sun_angular_size_smaxis = 0.533128;

//// Elements of the Moon's orbit, epoch 1980.0

// Moon's mean longitude at the epoch
double moon_mean_longitude_epoch = 64.975464;
// Mean longitude of the perigee at the epoch
double moon_mean_perigee_epoch = 349.383063;

// Mean longitude of the node at the epoch
double node_mean_longitude_epoch = 151.950429;

// Inclination of the Moon's orbit
double moon_inclination = 5.145396;

// Eccentricity of the Moon's orbit
double moon_eccentricity = 0.054900;

// Moon's angular size at distance a from Earth
double moon_angular_size = 0.5181;

// Semi-mojor axis of the Moon's orbit, in kilometers
double moon_smaxis = 384401.0;
// Parallax at a distance a from Earth
double moon_parallax = 0.9507;

// Synodic month (new Moon to new Moon), in days
double synodic_month = 29.53058868;

// Base date for E. W. Brown's numbered series of lunations (1923 January 16)
double lunations_base = 2423436.0;

//// Properties of the Earth

double earth_radius = 6378.16;
}

namespace c = constants;

namespace moon {

inline double fixangle(double a) {
    return a - 360.0 * floor(a/360.0);
}

inline double torad(double d) {
    return d * M_PI / 180.0;
}

inline double todeg(double r) {
    return r * 180.0 / M_PI;
}

inline double dsin(double d) {
    return sin(torad(d));
}

inline double dcos(double d) {
    return cos(torad(d));
}

enum PHASE {
    NEW = 1,
    WAXING_CRESCENT = 2,
    FIRST_QUARTER = 3,
    WAXING_GIBBOUS = 4,
    FULL = 5,
    WANING_GIBBOUS = 6,
    LAST_QUARTER = 7,
    WANING_CRESCENT = 8
};

    
inline PHASE phase_n(double p) {
    double PRECISION = 0.05;

    if (p <= 0 + PRECISION) {
        return NEW;

    } else if (p <= 0.25 - PRECISION) {
        return WAXING_CRESCENT;

    } else if (p <= 0.25 + PRECISION) {
        return FIRST_QUARTER;

    } else if (p <= 0.5 - PRECISION) {
        return WAXING_GIBBOUS;

    } else if (p <= 0.5 + PRECISION) {
        return FULL;

    } else if (p <= 0.75 - PRECISION) {
        return WANING_GIBBOUS;

    } else if (p <= 0.75 + PRECISION) {
        return LAST_QUARTER;

    } else if (p <= 1.0 - PRECISION) {
        return WANING_CRESCENT;

    } else if (p <= 1.0 + PRECISION) {
        return NEW;
    }

    return NEW;
}


inline std::string phase_string(PHASE p) {
    switch (p) {
    case NEW: return "new";
    case WAXING_CRESCENT: return "waxing crescent";
    case FIRST_QUARTER: return "first quarter";
    case WAXING_GIBBOUS: return "waxing gibbous";
    case FULL: return "full";
    case WANING_GIBBOUS: return "waning gibbous";
    case LAST_QUARTER: return "last quarter";
    case WANING_CRESCENT: return "waning crescent";
    }
    return "error";
}


inline double kepler(double m, double ecc) {
    // Solve the equation of Kepler.

    double epsilon = 1e-6;

    m = torad(m);
    double e = m;
    while (1) {
        double delta = e - ecc * sin(e) - m;
        e = e - delta / (1.0 - ecc * cos(e));

        if (fabs(delta) <= epsilon)
            break;
    }

    return e;
}


struct PhaseInfo {
    double phase_n;
    double illuminated;
    double age;
    double distance;
    double angular_diameter;
    double sun_distance;
    double sun_angular_diameter;
    PHASE phase;
    std::string phase_str;
};

  
inline PhaseInfo phase(time_t _phase_date=time(NULL)) {
    /** Calculate phase of moon as a fraction:

        The argument is the time for which the phase is requested.

        Returns a struct containing the terminator phase angle as a
        percentage of a full circle (i.e., 0 to 1), the illuminated
        fraction of the Moon's disc, the Moon's age in days and fraction,
        the distance of the Moon from the centre of the Earth, and the
        angular diameter subtended by the Moon as seen by an observer at
        the centre of the Earth. **/

    // Calculation of the Sun's position

    // Convert to JDN
    double phase_date = ((_phase_date / 86400) + 1) + 2440587.5;

    // date within the epoch
    double day = phase_date - c::epoch;

    // Mean anomaly of the Sun
    double N = fixangle((360/365.2422) * day);
    // Convert from perigee coordinates to epoch 1980
    double M = fixangle(N + c::ecliptic_longitude_epoch - c::ecliptic_longitude_perigee);

    // Solve Kepler's equation
    double Ec = kepler(M, c::eccentricity);
    Ec = sqrt((1 + c::eccentricity) / (1 - c::eccentricity)) * tan(Ec/2.0);
    // True anomaly
    Ec = 2 * todeg(atan(Ec));
    // Suns's geometric ecliptic longuitude
    double lambda_sun = fixangle(Ec + c::ecliptic_longitude_perigee);

    // Orbital distance factor
    double F = ((1 + c::eccentricity * cos(torad(Ec))) / pow(1 - c::eccentricity,2));;

    // Distance to Sun in km
    double sun_dist = c::sun_smaxis / F;
    double sun_angular_diameter = F * c::sun_angular_size_smaxis;

    /*
     *
     * Calculation of the Moon's position */

    // Moon's mean longitude
    double moon_longitude = fixangle(13.1763966 * day + c::moon_mean_longitude_epoch);

    // Moon's mean anomaly
    double MM = fixangle(moon_longitude - 0.1114041 * day - c::moon_mean_perigee_epoch);

    // Moon's ascending node mean longitude
    // MN = fixangle(c.node_mean_longitude_epoch - 0.0529539 * day)

    double evection = 1.2739 * sin(torad(2*(moon_longitude - lambda_sun) - MM));

    // Annual equation
    double annual_eq = 0.1858 * sin(torad(M));

    // Correction term
    double A3 = 0.37 * sin(torad(M));

    double MmP = MM + evection - annual_eq - A3;

    // Correction for the equation of the centre
    double mEc = 6.2886 * sin(torad(MmP));

    // Another correction term
    double A4 = 0.214 * sin(torad(2 * MmP));

    // Corrected longitude
    double lP = moon_longitude + evection + mEc - annual_eq + A4;

    // Variation
    double variation = 0.6583 * sin(torad(2*(lP - lambda_sun)));

    // True longitude
    double lPP = lP + variation;

    //
    // Calculation of the Moon's inclination
    // unused for phase calculation.
    
    // Corrected longitude of the node
    // NP = MN - 0.16 * sin(torad(M))

    // Y inclination coordinate
    // y = sin(torad(lPP - NP)) * cos(torad(c.moon_inclination))

    // X inclination coordinate
    // x = cos(torad(lPP - NP))

    // Ecliptic longitude (unused?)
    // lambda_moon = todeg(atan2(y,x)) + NP

    // Ecliptic latitude (unused?)
    // BetaM = todeg(asin(sin(torad(lPP - NP)) * sin(torad(c.moon_inclination))))

    /*
     *
     * Calculation of the phase of the Moon */

    // Age of the Moon, in degrees
    double moon_age = lPP - lambda_sun;

    // Phase of the Moon
    double moon_phase = (1 - cos(torad(moon_age))) / 2.0;

    // Calculate distance of Moon from the centre of the Earth
    double moon_dist = (c::moon_smaxis * pow(1 - c::moon_eccentricity,2)) / 
        (1 + c::moon_eccentricity * cos(torad(MmP + mEc)));

    // Calculate Moon's angular diameter
    double moon_diam_frac = moon_dist / c::moon_smaxis;
    double moon_angular_diameter = c::moon_angular_size / moon_diam_frac;

    // Calculate Moon's parallax (unused?)
    // moon_parallax = c.moon_parallax / moon_diam_frac

    double pp = fixangle(moon_age) / 360.0;
    PHASE ppn = phase_n(pp);

    PhaseInfo res;

    res.phase_n = pp;
    res.illuminated = moon_phase;
    res.age = c::synodic_month * fixangle(moon_age) / 360.0;
    res.distance = moon_dist;
    res.angular_diameter = moon_angular_diameter;
    res.sun_distance = sun_dist;
    res.sun_angular_diameter = sun_angular_diameter;
    res.phase = ppn;
    res.phase_str = phase_string(ppn);
    return res;
}


struct Moon {

    PhaseInfo pi;

    void init() {
        pi = phase();
    }

    //***  ***//

    inline void write(serialize::Sink& s) {
        serialize::write(s, pi.phase_n);
        serialize::write(s, pi.illuminated);
        serialize::write(s, pi.age);
        serialize::write(s, pi.distance);
        serialize::write(s, pi.angular_diameter);
        serialize::write(s, pi.sun_distance);
        serialize::write(s, pi.sun_angular_diameter);
        serialize::write(s, (unsigned int)pi.phase);
        serialize::write(s, pi.phase_str);
    }

    inline void read(serialize::Source& s) {
        serialize::read(s, pi.phase_n);
        serialize::read(s, pi.illuminated);
        serialize::read(s, pi.age);
        serialize::read(s, pi.distance);
        serialize::read(s, pi.angular_diameter);
        serialize::read(s, pi.sun_distance);
        serialize::read(s, pi.sun_angular_diameter);
        unsigned int phase;
        serialize::read(s, phase);
        pi.phase = (PHASE)phase;
        serialize::read(s, pi.phase_str);
    }
};


inline Moon& get() {
    static Moon ret;
    return ret;
}

}

#endif
