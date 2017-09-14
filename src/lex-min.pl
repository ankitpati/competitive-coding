#!/usr/bin/env perl

use strict;
use warnings;

<>;                     # discard n; we look for EOF anyways

my (@str1, @str2, @res);

sub lexcmp {
    my ($str1, $str2) = @_;

    my $i = 0;

    while ($i < @$str1 && $i < @$str2) {
        return 1 if $str1->[$i] lt $str2->[$i];
        return 0 if $str1->[$i] gt $str2->[$i];
        ++$i;
    }

    return 1 if @$str1 < @$str2;
    return 0 if @$str1 > @$str2;

    return 1;
}

while (<>) {
    chomp $_;           # string 1
    chomp (my $s = <>); # string 2

    @str1 = split '', $_;
    @str2 = split '', $s;
    @res  = ();

    while (@str1 && @str2) {
        push @res, lexcmp (\@str1, \@str2) ? shift @str1 : shift @str2;
    }

    while (@str1) {
        push @res, shift @str1;
    }

    while (@str2) {
        push @res, shift @str2;
    }

    print foreach @res;
    print "\n";
}
