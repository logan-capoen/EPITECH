/*
** EPITECH PROJECT, 2024
** my_compute_power_rec
** File description:
** recursive function that returns the first argument raised to the power p
*/

double my_compute_power_rec(int nb, int p)
{
    double result;

    result = nb;
    if (p == 0)
        return 1;
    else if (p < 0)
        return 0;
    else {
        result = my_compute_power_rec(nb, p - 1) * nb;
        return result;
    }
}
