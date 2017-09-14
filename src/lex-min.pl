#!/usr/bin/env perl

use strict;
use warnings;

<>;                     # discard n; we look for EOF anyways

my (@str1, @str2, @res, $len1, $len2);

sub lexcmp {
    my ($str1, $str2, $len1, $len2) = @_;

    for (0 .. ($len1 < $len2 ? $len1 : $len2) - 1) {
        return 1 if $str1->[$_] lt $str2->[$_];
        return 0 if $str1->[$_] gt $str2->[$_];
    }

    return 1 if $len1 < $len2;
    return 0 if $len1 > $len2;

    return 1;
}

while (<>) {
    chomp $_;           # string 1
    chomp (my $s = <>); # string 2

    @str1 = split '', $_;
    @str2 = split '', $s;
    @res  = ();

    while (($len1 = @str1) && ($len2 = @str2)) {
        push @res,
            lexcmp (\@str1, \@str2, $len1, $len2) ? shift @str1 : shift @str2;
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
