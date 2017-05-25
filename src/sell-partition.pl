#!/usr/bin/env perl

use strict;
use warnings;

sub partition {
    my ($n, $templist) = @_;
    my $partlist;

    $templist = { 1 => [[1]] } unless $templist;

    return $templist->{$n} if exists $templist->{$n};

    $partlist = [[$n]];

    foreach (1 .. $n-1) {
        my $rest = $n - $_;

        foreach my $part (@{partition ($_, $templist)}) {
            push @$partlist, [$rest, @$part] if $part->[0] <= $_;
        }
    }

    $templist->{$n} = $partlist;
    return $partlist;
}

sub seller {
    my $prices = shift;

    my @parts = keys %{{
        map { $_ => 1 }
        map { join ' ', @$_ }
        map { [sort @$_] }
        @{partition scalar @$prices}
    }}; # removes duplicate partitions

    my $max = 0;
    foreach (@parts) {
        my @elems = split;

        my $sum = 0;
        $sum += $prices->[$_ - 1] foreach @elems;

        $max = $sum if $sum > $max;
    }

    return $max;
}

my $num_input = <>;

my @input;
foreach (1 .. $num_input) {
    my $input = <>;
    chomp $input;
    push @input, $input;
}

print "${\seller \@input}\n";
