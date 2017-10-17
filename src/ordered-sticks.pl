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
    $lis[0] = [$sticks[0]];
    foreach my $i (1 .. $#sticks) {
        my ($longest, $longest_j);
        foreach my $j (0 .. $i-1) {
            if ($lis[$j][-1] <= $sticks[$i]) {
                my $lis_count = @{$lis[$j]};
                if ($lis_count > ($longest // 0)) {
                    $longest = $lis_count;
                    $longest_j = $j;
                }
            }
        }

        $lis[$i] = [defined $longest ? @{$lis[$longest_j]} : (), $sticks[$i]];

        my $elems = @{$lis[$i]};
        $maximum = $elems if $elems > $maximum;
    }

    print "$maximum\n";
}
