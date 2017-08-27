#!/usr/bin/env perl

use strict;
use warnings;

<>;                         # discard n; we are going to look for EOF anyways

my @unsorted;
my $maxlen = 0;

while (<>) {
    chomp $_;
    push @unsorted, $_;
    $maxlen = length $_ if $maxlen < length $_;
}

$_ = '0'x($maxlen - length $_) . $_ foreach @unsorted;
@unsorted = sort @unsorted; # optimises to in-place sort
s/^0+// foreach @unsorted;

print "$_\n" foreach @unsorted;
