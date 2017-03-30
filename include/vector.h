/*
   Copyright (C) 2014 - 2016 Mutzii

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef VECTOR_H
#define VECTOR_H

template< typename A>
class Vector2
{
    public:
        Vector2(void);
        Vector2(A x , A y);
        ~Vector2(void)=default;

        Vector2 & operator=( const Vector2 & );

        Vector2 & operator-( const Vector2 &l);

        Vector2 & operator+(const Vector2& );

        Vector2 & operator*(const Vector2& );
        Vector2 & operator*(const A );

        bool operator ==( const Vector2 &);

        bool operator !=( const Vector2 &);

        void normalize(void);

        void setX(A x );
        void setY(A y);

        A getX(void) const;
        A getY(void) const;

    private:
        A mX, mY; /*!< TODO */
};

template < typename A>
class Vector3
{
    public:
        Vector3(void);
        Vector3( A x , A y , A z);
        ~Vector3(void) =default;

        Vector3 & operator=( const Vector3& );

        Vector3 & operator+=(const Vector3& );

        Vector3 & operator+(const Vector3& );

        Vector3 & operator-(const Vector3& );

        Vector3 & operator*(const Vector3& );

        bool operator<(const Vector3 & ) const;

        Vector3 & operator*(const A );

        bool operator ==( const Vector3 &) const;
        bool operator !=( const Vector3 &) const;

        void normalize(void);
        void inverse(void);

        void setX(A x);
        void setY(A y);
        void setZ(A z);

        A getX(void) const;
        A getY(void) const;
        A getZ(void) const;

    private:
        A mX , mY , mZ; /*!< TODO */
 };

    template < typename A>
    class Vector4
    {
        public:
            Vector4(void);
            Vector4( A x , A y , A z , A a);
            ~Vector4(void) = default;

            Vector4 & operator=( const Vector4& );

            Vector4 & operator+=(const Vector4& );

            Vector4 & operator+(const Vector4& );
            Vector4 & operator+(const Vector3<A>& );
            Vector4 & operator+(const Vector2<A>& );

            Vector4 & operator-(const Vector4& );
            Vector4 & operator-(const Vector3<A>& );
            Vector4 & operator-(const Vector2<A>& );

            Vector4 & operator*(const Vector4& );
            Vector4 & operator*(const A );

            bool operator ==( const Vector4 &);
            bool operator !=( const Vector4 &);

            void setX(A x);
            void setY(A y);
            void setZ(A z);
            void setA(A a);

            A getX(void) const;
            A getY(void) const;
            A getZ(void) const;
            A getA(void) const;

        private:
            A mX , mY , mZ , mA; /*!< TODO */
    };

    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;
    using Vector2i = Vector2<int>;

    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;
    using Vector3i = Vector3<int>;

    using Vector4f = Vector4<float>;
    using Vector4d = Vector4<double>;
    using Vector4i = Vector4<int>;

    /* ------------ no templates --------------*/

    /* vector source code / template */
    #include "vector.template"

#endif // VECTOR2_H
