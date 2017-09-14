#!/usr/bin/env perl

use strict;
use warnings;

chomp ($_ = <>);

while (s/(.)\1//g) { }

print 'Empty String' unless $_;
print "$_\n";
