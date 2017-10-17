#!/usr/bin/env perl

use strict;
use warnings;

<>; # discard t; we will read till EOF anyways

while (<>) {
    my (undef, @sticks) = split; # discard n; we process the remaining elements

    unless (@sticks) {
        print "0\n";
        next;
    }

    my $maximum = 1;

    my @lis;
    $lis[0] = [1, $sticks[0]];
    foreach my $i (1 .. $#sticks) {
        my $longest;
        foreach my $j (0 .. $i-1) {
            if ($lis[$j][-1] <= $sticks[$i]) {
                $longest = $lis[$j][0] if ($lis[$j][0] > ($longest // 0));
            }
        }

        $lis[$i] = [($longest // 0) + 1, $sticks[$i]];
        $maximum = $lis[$i][0] if $lis[$i][0] > $maximum;
    }

    print "$maximum\n";
}
