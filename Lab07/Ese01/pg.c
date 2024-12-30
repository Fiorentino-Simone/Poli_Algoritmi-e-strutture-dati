#include "pg.h"

int pg_read(FILE *fp, pg_t *pgp)
{
    int ret;
    ret = fscanf(fp, "%s %s %s",
                pgp->cod,
                pgp->nome,
                pgp->classe);

    if (ret == 3)
    {
        stat_read(fp, &(pgp->b_stat));
        pgp->eq_stat = pgp->b_stat;
        pgp->equip = equipArray_init();
        return 1;
    }
    return 0;
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray)
{
    printf("%s %s %s",
            pgp->cod,
            pgp->nome,
            pgp->classe);
    stat_print(fp, &(pgp->eq_stat), 1);
    equipArray_print(fp, pgp->equip, invArray);
    printf("\n");
}

void pg_clean(pg_t *pgp)
{
    equipArray_free(pgp->equip);
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray)
{
    equipArray_update(pgp->equip, invArray);

    stat_t stat = equipArray_getLastStat(pgp->equip, invArray);
    pgp->eq_stat.hp += stat.hp;
    pgp->eq_stat.mp += stat.mp;
    pgp->eq_stat.atk += stat.atk;
    pgp->eq_stat.def += stat.def;
    pgp->eq_stat.mag += stat.mag;
    pgp->eq_stat.spr += stat.spr;
}