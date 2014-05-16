/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2014 Elias Tsigaridas

******************************************************************************/

/* Returns the sign of F(1/2) */
int fmpz_poly_sgn_eval_at_half (fmpz_poly_t P)
{
	long j, p;
	int ret;
	fmpz_t x, y;
    
    long deg = fmpz_poly_degree(P);
    
	fmpz_init(y);
	fmpz_init_set_ui(x, 0);

	p = deg + 1;
	for (j = 0; j <= deg; j++, p--)
    {
		fmpz_mul_2exp(y, fmpz_poly_get_coeff_ptr(P, j), p);
		fmpz_add(x, x, y);
	}

	fmpz_clear(y);
	ret = fmpz_sgn(x);
	fmpz_clear(x);
	return ret;
}

