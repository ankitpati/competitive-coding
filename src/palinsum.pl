#!/usr/bin/env perl

use strict;
use warnings;

my $me = (split m{/}, $0)[-1];

die "Usage: $me <+ve integer>...\n" if !@ARGV or grep !/^\d+$/, @ARGV;

local $, = ' ';

foreach my $num (@ARGV) {
    print "$num: ";
    print grep { $_ + reverse == $num } 0 .. $num;
    print "\n";
}
