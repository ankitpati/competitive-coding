#!/usr/bin/env perl

use strict;
use warnings;

print "Enter a string of ones (1) to know if the length is prime.\n";

#my $prime_length_regex = qr/^1?$|^(11+?)\1+$/;

my $ones = <>;

print ($ones =~ /^1?$|^(11+?)\1+$/ ? "Not Prime" : "Prime", "\n");
