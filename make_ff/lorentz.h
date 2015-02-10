namespace {

        double angular_range_reduce(const double x)
        {
                const double cody_waite_x_max = 1608.4954386379741381;
                const double two_pi_0 = 6.2831853071795649157;
                const double two_pi_1 = 2.1561211432631314669e-14;
                const double two_pi_2 = 1.1615423895917441336e-27;
                double ret;

                if (x >= -cody_waite_x_max && x <= cody_waite_x_max) {
                        const double inverse_two_pi =
                                0.15915494309189534197;
                        const double k = TMath::Nint(x * inverse_two_pi);
                        ret = ((x - (k * two_pi_0)) - k * two_pi_1) -
                                k * two_pi_2;
                }
                else {
                        long double sin_x;
                        long double cos_x;

                        sincosl(x, &sin_x, &cos_x);
                        ret = (double)atan2l(sin_x, cos_x);
                }
                if (ret == -TMath::Pi()) {
                        ret = TMath::Pi();
                }

                return ret;
        }

    class lorentz_vector_t {
    protected:
                double _x[4];
    public:
                lorentz_vector_t(void)
                {
                }
                lorentz_vector_t(const double time_, const double x_,
                                                 const double y_, const double z_)
                {
                        _x[0] = time_;
                        _x[1] = x_;
                        _x[2] = y_;
                        _x[3] = z_;
                }
                lorentz_vector_t(const double time_, const double x_[3])
                {
                        _x[0] = time_;
                        _x[1] = x_[0];
                        _x[2] = x_[1];
                        _x[3] = x_[2];
                }
                lorentz_vector_t(const double x_[4])
                {
                        _x[0] = x_[0];
                        _x[1] = x_[1];
                        _x[2] = x_[2];
                        _x[3] = x_[3];
                }

                void set_energy(const double e)
                {
                        _x[0] = e;
                }

                double operator[](const int n) const
                {
                        return _x[n];
                }

                double &operator[](const int n)
                {
                        return _x[n];
                }

                double time(void) const
                {
                        return _x[0];
                }

                double &time(void)
                {
                        return _x[0];
                }

                double &energy(void)
                {
                        return _x[0];
                }

                double x(void) const
                {
                        return _x[1];
                }

                double &x(void)
                {
                        return _x[1];
                }

                double y(void) const
                {
                        return _x[2];
                }

                double &y(void)
                {
                        return _x[2];
                }

                double z(void) const
                {
                        return _x[3];
                }

                double &z(void)
                {
                        return _x[3];
                }

                lorentz_vector_t operator*(const double s) const
                {
                        return lorentz_vector_t(_x[0] * s, _x[1] * s,
                                                _x[2] * s, _x[3] * s);
                }

                double perp(void) const
                {
                        return sqrt(_x[1] * _x[1] + _x[2] * _x[2]);
                }

                double azimuth(void) const
                {
                        return atan2(_x[2], _x[1]);
                }

                double height(void) const
                {
                        return z();
                }

                lorentz_vector_t
                operator+(const lorentz_vector_t &v) const
                {
                        return lorentz_vector_t(
                                _x[0] + v._x[0], _x[1] + v._x[1],
                                _x[2] + v._x[2], _x[3] + v._x[3]);
                }

                lorentz_vector_t
                operator+=(const lorentz_vector_t &v)
                {
                        _x[0] += v._x[0];
                        _x[1] += v._x[1];
                        _x[2] += v._x[2];
                        _x[3] += v._x[3];

                        return *this;
                }

                lorentz_vector_t
                operator-(const lorentz_vector_t &v) const
                {
                        return lorentz_vector_t(
                                _x[0] - v._x[0], _x[1] - v._x[1],
                                _x[2] - v._x[2], _x[3] - v._x[3]);
                }

                lorentz_vector_t
                operator-=(const lorentz_vector_t &v)
                {
                        _x[0] -= v._x[0];
                        _x[1] -= v._x[1];
                        _x[2] -= v._x[2];
                        _x[3] -= v._x[3];

                        return *this;
                }
                lorentz_vector_t transverse(const lorentz_vector_t &v) const
                {
                        const float s = cartesian_dot(v) /
                                v.cartesian_magnitude_square();

                        const lorentz_vector_t ret = *this - v * s;

                        return ret;
                }

                double transverse_magnitude(const lorentz_vector_t &v) const
                {
                        const lorentz_vector_t t = transverse(v);

                        return t.cartesian_magnitude();
                }

                bool operator==(const double c) const
                {
                        return (_x[0] == c && _x[1] == c &&
                                        _x[2] == c && _x[3] == c);
                }

                bool operator!=(const double c) const
                {
                        return (_x[0] != c || _x[1] != c ||
                                        _x[2] != c || _x[3] != c);
                }

                double cartesian_magnitude_square(void) const
                {
                        const float s = x() * x() + y() * y() + z() * z();

                        return s;
                }

                double cartesian_magnitude(void) const
                {
                        return sqrt(cartesian_magnitude_square());
                }

                double cartesian_dot(const lorentz_vector_t &v) const
                {
                        const double s = x() * v.x() + y() * v.y() + z() * v.z();

                        return s;
                }

                double longitudinal_fraction_of(const lorentz_vector_t &v) const
                {
                        return cartesian_dot(v) / v.cartesian_magnitude_square();
                }

        };

        class snowmass_vector_t {
        protected:
                double _x[4];
        public:
                snowmass_vector_t(void)
                {
                }

                snowmass_vector_t(const double vector[4])
                {
                        _x[0] = vector[0];
                        _x[1] = vector[1];
                        _x[2] = vector[2];
                        _x[3] = vector[3];
                }

                snowmass_vector_t(const double time_, const double perp_,
                                                  const double pseudorapidity_,
                                                  const double azimuth_)
                {
                        _x[0] = time_;
                        _x[1] = perp_;
                        _x[2] = pseudorapidity_;
                        _x[3] = angular_range_reduce(azimuth_);
                }

                snowmass_vector_t(lorentz_vector_t v)
                {
                        set_time(v[0]);
                        set_x_y_z(v[1], v[2], v[3]);
                }
               
                void set_time(const double time_)
                {
                        _x[0] = time_;
                }
                void set_perp_pseudorapidity_azimuth(
                        const double perp_, const double pseudorapidity_,
                        const double azimuth_)
                {
                        _x[1] = perp_;
                        _x[2] = pseudorapidity_;
                        _x[3] = angular_range_reduce(azimuth_);
                }
                void set_x_y_z(const double x_, const double y_,
                                           const double z_)
                {
                        const double perp_square_ = x_ * x_ + y_ * y_;

                        _x[1] = sqrt(perp_square_);

                        const double magnitude_square = perp_square_ + z_ * z_;

                        if (perp_square_ == 0) {
                                _x[2] = (z_ >= 0 ? 1e+12 : -1e+12);
                        }
                        else {      
                            if (perp_square_ < M_SQRT1_2 * magnitude_square) {
                               const double half_sign = z_ > 0 ? 0.5 : -0.5;
                               const double sin_polar_angle_square = perp_square_ / magnitude_square;
_x[2] = half_sign *
                                                log((2.0 - sin_polar_angle_square + 2.0 *
                                                         sqrt(1.0 - sin_polar_angle_square)) /
                                                        sin_polar_angle_square);
                                }
                                else {
                                        const double cos_polar_angle_ =
                                                magnitude_square == 0 ?
                                                1.0 : z_ / sqrt(magnitude_square);

                                        _x[2] = atanh(cos_polar_angle_);
                                }
                                _x[2] = (_x[1] >= 0 ? 1e+12 : -1e+12);
                        }
_x[3] = (x_ == 0 && y_ == 0) ? 0.0 : atan2(y_, x_);
                }

                double *data(void)
                {
                        return _x;
                }

                const double *data(void) const
                {
                        return _x;
                }

                double &operator[](const int idx)
                {
                        return _x[idx];
                }
                double &time(void)
                {
                        return _x[0];
                }
                double time(void) const
                {
                        return _x[0];
                }

                double &perp(void)
                {
                        return _x[1];
                }

                double perp(void) const
                {
                        return _x[1];
                }

                double perp_square(void) const
                {
                        return _x[1] * _x[1];
                }

                double &pseudorapidity(void)
                {
                        return _x[2];
                }

                double pseudorapidity(void) const
                {
                        return _x[2];
                }

                double &azimuth(void)
                {
                        return _x[3];
                }

                double azimuth(void) const
                {
                        return _x[3];
                }
                double x(void) const
                {
                        const double __perp = perp();
                        const double __azimuth = azimuth();

                        return __perp * cos(__azimuth);
                }
                double y(void) const
                {
                        const double __perp = perp();
                        const double __azimuth = azimuth();

                        return __perp * sin(__azimuth);
                }
                double z(void) const
                {
                        const double __perp = perp();
                        const double __pseudorapidity = pseudorapidity();

                        return __perp * sinh(__pseudorapidity);
                }

                double cartesian_magnitude(void) const
                {
                        const double perp_ = _x[1], eta = _x[2];
                const double s = cosh(eta);

                        return perp_ * s;
                }
                double cartesian_magnitude_square(void) const
                {
                        const double s = cartesian_magnitude();

                        return s * s;
                }
                double cos_polar_angle(void) const
                {
                        return tanh(_x[2]);
                }
                double sin_polar_angle(void) const
                {
                        return 1 / cosh(_x[2]);
                }

                double cartesian_dot(const snowmass_vector_t &v) const
                {
                       return _x[1] * v._x[1] *
                                (cos(_x[3] - v._x[3]) + sinh(_x[2]) * sinh(v._x[2]));
                }

                snowmass_vector_t operator*(const double s) const
                {
                        return snowmass_vector_t(_x[0] * s, _x[1] * s,
                                                                         _x[2], _x[3]);
                }

                operator lorentz_vector_t(void) const
                {
                        return lorentz_vector_t(time(), x(), y(), z());
                }

                double radial_distance_square(const snowmass_vector_t &v)
                        const
                {
                        const double pseudorapidity_difference =
                                v.pseudorapidity() - pseudorapidity();
                        const double azimuth_difference =
                                angular_range_reduce(v.azimuth() - azimuth());

                        return
                                pseudorapidity_difference *
                                pseudorapidity_difference +
                                azimuth_difference * azimuth_difference;
                }
                double radial_distance(const snowmass_vector_t &v) const
                {
                        return sqrt(radial_distance_square(v));
                }

                double longitudinal_fraction_of(const snowmass_vector_t &v)
                        const
                {
                        return cartesian_dot(v) / v.cartesian_magnitude_square();
                }
                void set_lightlike_perp(void)
                {
                        _x[1] = _x[0] * sin_polar_angle();
                }
                void set_lightlike_time(void)
                {
                        const double st = sin_polar_angle();

                        if (st == 0) {
                                _x[0] = 1e+12;
                        }
                        else {
                                _x[0] = _x[1] / st;
                        }
                }
        };
}

