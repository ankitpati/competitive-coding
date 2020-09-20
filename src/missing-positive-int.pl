#!/usr/bin/env perl

use strict;
use warnings;

sub solution {
    my %h;
    undef @h{@_};

    @_ = sort { $a <=> $b } grep { $_ > 0 } keys %h;

    for (my $i = 0; $i < @_; ++$i) {
        return $i + 1 if $_[$i] != $i + 1;
    }

    return 1 + scalar @_;
}

my @a;
push @a, $_ foreach  102..200; #  102 to 200, both inclusive
push @a, $_ foreach    0..100; #    0 to 100, both inclusive
push @a, $_ foreach -200.. 50; # -200 to  50, both inclusive

print "${\(solution @a)}\n";  # Missing Number: 101
