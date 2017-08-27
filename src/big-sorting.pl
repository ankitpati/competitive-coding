#!/usr/bin/env perl

use strict;
use warnings;

<>;                         # discard n; we are going to look for EOF anyways

my @unsorted;

while (<>) {
    chomp $_;
    push @unsorted, $_;
}

@unsorted = sort {          # optimises to in-place sort
    my $len = length ($a) - length ($b);
    return $len if $len;    # two-level sort: sort by value only
    return $a cmp $b;       #                 if lengths match.
} @unsorted;

print "$_\n" foreach @unsorted;
