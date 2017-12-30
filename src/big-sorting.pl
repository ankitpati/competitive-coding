#!/usr/bin/env perl

use strict;
use warnings;

<>;                         # discard n; we are going to look for EOF anyways

print "$_\n" foreach sort {
    my $len = length ($a) - length ($b);
    return $len if $len;    # two-level sort: sort by value only
    return $a cmp $b;       #                 if lengths match.
} map { chomp; $_ } <>;
