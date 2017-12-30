#!/usr/bin/env perl

use strict;
use warnings;

my ($n) = split ' ', <>;

chomp (my $c = <>);
my @c = sort { $a <=> $b } split ' ', $c;

my %hash;

sub countp {
    my $n = shift;

    return $n ? $n < ($_[0] || 0) ? 0 : @_ ?
                countp ($n - $_[0], @_) + countp ($n, @_[1 .. $#_])
                : 0 : 1;
}

print (countp ($n, @c));
