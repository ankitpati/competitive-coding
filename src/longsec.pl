#!/usr/bin/env perl

use strict;
use warnings;

<>;

my $reg;

foreach (<>) {
    chomp;
    /^(.)/;
    $reg = "^$1*?[^$1]$1*?\$";
    print (/$reg/ ? "Yes" : "No", "\n");
}
