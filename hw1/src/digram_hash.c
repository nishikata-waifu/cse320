#include "const.h"
#include "sequitur.h"

/*
 * Digram hash table.
 *
 * Maps pairs of symbol values to first symbol of digram.
 * Uses open addressing with linear probing.
 * See, e.g. https://en.wikipedia.org/wiki/Open_addressing
 */

/**
 * Clear the digram hash table.
 */
void init_digram_hash(void) {
    // To be implemented.
    for (int i=0; i<MAX_DIGRAMS;i++)
    {
        *(digram_table+i) = NULL;
    }
}

/**
 * Look up a digram in the hash table.
 *
 * @param v1  The symbol value of the first symbol of the digram.
 * @param v2  The symbol value of the second symbol of the digram.
 * @return  A pointer to a matching digram (i.e. one having the same two
 * symbol values) in the hash table, if there is one, otherwise NULL.
 */
SYMBOL *digram_get(int v1, int v2) {
    // To be implemented.
    int i = DIGRAM_HASH(v1, v2);
    SYMBOL* dg = *(digram_table+i);
    int si = i;
    while (dg != NULL)
    {
        if (dg == TOMBSTONE) 
        {
            i++;
            if (i == si) break;
            if (i == MAX_DIGRAMS) i = 0;
            dg = *(digram_table+i);
            continue;
        }
        if ((dg)-> value == v1 && (dg -> next) -> value == v2)
        {
            return dg;
        }
        i++;
        if (i == si) break;
        if (i == MAX_DIGRAMS)
        {
            i = 0;
        }
        dg = *(digram_table+i);
    }
    return NULL;
}


/**
 * Delete a specified digram from the hash table.
 *
 * @param digram  The digram to be deleted.
 * @return 0 if the digram was found and deleted, -1 if the digram did
 * not exist in the table.
 *
 * Note that deletion in an open-addressed hash table requires that a
 * special "tombstone" value be left as a replacement for the value being
 * deleted.  Tombstones are treated as vacant for the purposes of insertion,
 * but as filled for the purpose of lookups.
 *
 * Note also that this function will only delete the specific digram that is
 * passed as the argument, not some other matching digram that happens
 * to be in the table.  The reason for this is that if we were to delete
 * some other digram, then somebody would have to be responsible for
 * recycling the symbols contained in it, and we do not have the information
 * at this point that would allow us to be able to decide whether it makes
 * sense to do it here.
 */
int digram_delete(SYMBOL *digram) {
    // To be implemented.
    int v1 = digram -> value;
    if (digram -> next == NULL)
    {
        return -1;
    }
    int v2 = digram -> next -> value;
    int i = DIGRAM_HASH(v1, v2);
    SYMBOL* dg = *(digram_table+i);
    int si = i;
    while (dg != NULL)
    {
        if (dg == TOMBSTONE) 
        {
            i++;
            if (i == si) return -1;
            if (i == MAX_DIGRAMS) i = 0;
            dg = *(digram_table+i);
            continue;
        }
        if (dg == digram && (dg ->next) == (digram-> next))
        {
            *(digram_table+i) = TOMBSTONE;
            return 0;
        }
        i++;
        if (i == si) return -1;
        if (i == MAX_DIGRAMS)
        {
            i = 0;
        }
        dg = *(digram_table+i);
    }
    return -1;
}

/**
 * Attempt to insert a digram into the hash table.
 *
 * @param digram  The digram to be inserted.
 * @return  0 in case the digram did not previously exist in the table and
 * insertion was successful, 1 if a matching digram already existed in the
 * table and no change was made, and -1 in case of an error, such as the hash
 * table being full or the given digram not being well-formed.
 */
int digram_put(SYMBOL *digram) {
    // To be implemented.
    int v1 = digram -> value;
    if (digram -> next == NULL)
    {
        return -1;
    }
    int v2 = digram -> next -> value;
    int i = DIGRAM_HASH(v1, v2);
    SYMBOL* dg = *(digram_table+i);
    int si = i;
    while (dg != NULL)
    {
        if (dg == TOMBSTONE) 
        {
            *(digram_table+i) = digram;
            return 0;
        }
        if ((dg -> next) == NULL) return -1;
        if ((dg)-> value == v1 && (dg -> next) -> value == v2)
        {
            return 1;
        }
        i++;
        if (i == si) return -1;
        if (i == MAX_DIGRAMS)
        {
            i = 0;
        }
        dg = *(digram_table+i);
    }
    if (dg == NULL)
    {
        *(digram_table+i) = digram;
        return 0;
    }
    return -1;
}
