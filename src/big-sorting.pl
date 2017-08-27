#!/usr/bin/env perl

use strict;
use warnings;

<>;

my @unsorted;
my $maxlen = 0;

while (<>) {
    chomp $_;
    push @unsorted, $_;
    $maxlen = length $_ if $maxlen < length $_;
}

print "$_\n" foreach
         map { s/^0+//r } sort map { '0'x($maxlen - length $_) . $_ } @unsorted;
