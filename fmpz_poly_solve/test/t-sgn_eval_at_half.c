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

    Copyright (C) 2014 Fredrik Johansson

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "fmpz_poly_solve.h"

int
main(void)
{
    int iter;
    FLINT_TEST_INIT(state);

    flint_printf("sgn_eval_at_half....");
    fflush(stdout);

    /* Check aliasing */
    for (iter = 0; iter < 1000 * flint_test_multiplier(); iter++)
    {
        fmpz_t a;
        fmpz_poly_t f, g;
        long i, d;
        int s1, s2;

        fmpz_init(a);
        fmpz_poly_init(f);
        fmpz_poly_init(g);

        fmpz_poly_randtest(f, state, n_randint(state, 100), 200);

        s1 = fmpz_poly_sgn_eval_at_half(f);

        fmpz_poly_set(g, f);
        d = fmpz_poly_degree(g);
        for (i = 0; i <= d; i++)
        {
            fmpz_mul_2exp(fmpz_poly_get_coeff_ptr(g, i),
                          fmpz_poly_get_coeff_ptr(g, i), d - i);
        }

        fmpz_one(a);
        fmpz_poly_evaluate_fmpz(a, g, a);

        s2 = fmpz_sgn(a);

        if (s1 != s2)
        {
            flint_printf("FAIL:\n");
            fmpz_poly_print(f); printf("\n\n");
            printf("s1 = %d, s2 = %d\n\n", s1, s2);
            abort();
        }

        fmpz_clear(a);
        fmpz_poly_clear(f);
        fmpz_poly_clear(g);
    }

    FLINT_TEST_CLEANUP(state);
    flint_printf("PASS\n");
    return 0;
}

