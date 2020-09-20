#!/usr/bin/env perl

use strict;
use warnings;

sub solution {
    my $packed_int = pack 'L', shift;

    my ($current_run, $max_run) = (undef, 0);
    foreach (split //, unpack 'B*', reverse $packed_int) {
        if ($_) {
            # 1
            $max_run = $current_run if $current_run and $current_run > $max_run;
            $current_run = 0;
        }
        else {
            # 0
            next if not defined $current_run;
            ++$current_run;
        }
    }

    return $max_run;
}

print "${\(solution 1041)}\n";
