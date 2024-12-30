#include "inv.h"

void stat_read(FILE *fp, stat_t *statp)
{
    fscanf(fp, "%d %d %d %d %d %d",
            &(statp->hp),
            &(statp->mp),
            &(statp->atk),
            &(statp->def),
            &(statp->mag),
            &(statp->spr));
}

void inv_read(FILE *fp, inv_t *invp)
{
    fscanf(fp, "%s %s",
            invp->nome,
            invp->tipo);

    stat_read(fp, &(invp->stat));
}

void stat_print(FILE *fp, stat_t *statp, int soglia)
{
    // se soglia == -1 allora è stata richiamata dall'equipaggiamento che non ha bisogno del controllo che la statistica sia > 1
    printf(" ");
    if (soglia == -1)
    {
        fprintf(fp, "%d %d %d %d %d %d",
                (statp->hp),
                (statp->mp),
                (statp->atk),
                (statp->def),
                (statp->mag),
                (statp->spr));
    }
    else
    {
        fprintf(fp, "%d %d %d %d %d %d",
                (statp->hp < 1 ? 1 : statp->hp),
                (statp->mp < 1 ? 1 : statp->mp),
                (statp->atk < 1 ? 1 : statp->atk),
                (statp->def < 1 ? 1 : statp->def),
                (statp->mag < 1 ? 1 : statp->mag),
                (statp->spr < 1 ? 1 : statp->spr));
    }
}

void inv_print(FILE *fp, inv_t *invp)
{
    fprintf(fp, "%s %s",
            invp->nome,
            invp->tipo);
    stat_print(fp, &(invp->stat), -1);
}

stat_t inv_getStat(inv_t *invp)
{
    return invp->stat;
}