#!/usr/bin/perl
use strict;
use File::Copy;

use constant {
  NORMAL => 0,
  FE_CAPS => 1,
  FE_STATUS => 2,
  FE_CODERATE => 3,
  FE_MODULATION => 4,
  FE_TMODE => 5,
  FE_BW => 6,
  FE_GINTERVAL => 7,
  FE_HIERARCHY => 8,
  FE_DTS => 9,
  FE_VOLTAGE => 10,
  FE_TONE => 11,
  FE_INVERSION => 12,
  FE_PILOT => 13,
  FE_ROLLOFF => 14,
};

my $dir = shift or die "Please specify the kernel include directory.";

#
# Put it into a canonical form
#
$dir =~ s,/$,,;
$dir =~ s,/dvb$,,;
$dir =~ s,/linux$,,;

my %fe_caps;
my %fe_status;
my %fe_code_rate;
my %fe_modulation;
my %fe_t_mode;
my %fe_bw;
my %fe_guard_interval;
my %fe_hierarchy;
my %dvb_v5;
my %fe_delivery_system;
my %fe_voltage;
my %fe_tone;
my %fe_inversion;
my %fe_pilot;
my %fe_rolloff;

sub gen_fe($)
{
  my $file = shift;

  my $mode = 0;

  open IN, "<$file" or die "Can't open $file";

  while (<IN>) {
    #
    # Mode FE_CAPS
    #
<<<<<<< HEAD
<<<<<<< HEAD
    if (m/enum fe_caps\ \{/) {
=======
    if (m/typedef enum fe_caps\ {/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
    if (m/typedef enum fe_caps\ {/) {
=======
    if (m/enum fe_caps\ \{/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
      $mode = FE_CAPS;
      next;
    }
    if ($mode == FE_CAPS) {
<<<<<<< HEAD
<<<<<<< HEAD
      if (m/\};/) {
=======
      if (m/\} fe_caps_t;/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
      if (m/\} fe_caps_t;/) {
=======
      if (m/\};/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
        $mode = NORMAL;
        next;
      }
      if (m/(FE_)([^\s,=]+)/) {
        my $macro = "$1$2";
        my $name = $2;

        $fe_caps{$macro} = $name;
      }
    }
    #
    # Mode FE_STATUS
    #
<<<<<<< HEAD
<<<<<<< HEAD
    if (m/enum fe_status\ \{/) {
=======
    if (m/typedef enum fe_status\ {/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
    if (m/typedef enum fe_status\ {/) {
=======
    if (m/enum fe_status\ \{/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
      $mode = FE_STATUS;
      next;
    }
    if ($mode == FE_STATUS) {
<<<<<<< HEAD
<<<<<<< HEAD
      if (m/\};/) {
=======
      if (m/\} fe_status_t;/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
      if (m/\} fe_status_t;/) {
=======
      if (m/\};/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
        $mode = NORMAL;
        next;
      }
      if (m/(FE_)([^\s,=]+)/) {
        my $macro = "$1$2";
        my $name = $2;

        $name =~ s/HAS_//;

        $fe_status{$macro} = $name;
      }
    }
    #
    # Mode FE_CODERATE
    #
<<<<<<< HEAD
<<<<<<< HEAD
    if (m/enum fe_code_rate \{/) {
=======
    if (m/typedef enum fe_code_rate \{/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
    if (m/typedef enum fe_code_rate \{/) {
=======
    if (m/enum fe_code_rate \{/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
      $mode = FE_CODERATE;
      next;
    }
    if ($mode == FE_CODERATE) {
<<<<<<< HEAD
<<<<<<< HEAD
      if (m/\};/) {
=======
      if (m/\} fe_code_rate_t;/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
      if (m/\} fe_code_rate_t;/) {
=======
      if (m/\};/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
        $mode = NORMAL;
        next;
      }
      if (m/(FEC_)([^\s,]+)/) {
        my $macro = "$1$2";
        my $name = $2;
        $name =~ s,_,/,;

        $fe_code_rate{$macro} = $name;
      }
    }
    #
    # Mode FE_MODULATION
    #
<<<<<<< HEAD
<<<<<<< HEAD
    if (m/enum fe_modulation \{/) {
=======
    if (m/typedef enum fe_modulation \{/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
    if (m/typedef enum fe_modulation \{/) {
=======
    if (m/enum fe_modulation \{/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
      $mode = FE_MODULATION;
      next;
    }
    if ($mode == FE_MODULATION) {
<<<<<<< HEAD
<<<<<<< HEAD
      if (m/\};/) {
=======
      if (m/\} fe_modulation_t;/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
      if (m/\} fe_modulation_t;/) {
=======
      if (m/\};/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
        $mode = NORMAL;
        next;
      }
      if (m/\t([^\s,=]+)/) {
        my $macro = "$1";
        my $name = $1;
        $name =~ s,_,/,;

        $fe_modulation{$macro} = $name;
      }
    }
    #
    # Mode FE_TMODE
    #
<<<<<<< HEAD
<<<<<<< HEAD
    if (m/enum fe_transmit_mode \{/) {
=======
    if (m/typedef enum fe_transmit_mode \{/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
    if (m/typedef enum fe_transmit_mode \{/) {
=======
    if (m/enum fe_transmit_mode \{/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
      $mode = FE_TMODE;
      next;
    }
    if ($mode == FE_TMODE) {
<<<<<<< HEAD
<<<<<<< HEAD
      if (m/\};/) {
=======
      if (m/\} fe_transmit_mode_t;/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
      if (m/\} fe_transmit_mode_t;/) {
=======
      if (m/\};/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
        $mode = NORMAL;
        next;
      }
      if (m/(TRANSMISSION_MODE_)([^\s,=]+)/) {
        my $macro = "$1$2";
        my $name = $2;
        $name =~ s,_,/,;

        $fe_t_mode{$macro} = $name;
      }
    }
    #
    # Mode FE_BW
    #
<<<<<<< HEAD
<<<<<<< HEAD
    if (m/enum fe_bandwidth \{/) {
=======
    if (m/typedef enum fe_bandwidth \{/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
    if (m/typedef enum fe_bandwidth \{/) {
=======
    if (m/enum fe_bandwidth \{/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
      $mode = FE_BW;
      next;
    }
    if ($mode == FE_BW) {
<<<<<<< HEAD
<<<<<<< HEAD
      if (m/\};/) {
=======
      if (m/\} fe_bandwidth_t;/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
      if (m/\} fe_bandwidth_t;/) {
=======
      if (m/\};/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
        $mode = NORMAL;
        next;
      }
      if (m/(BANDWIDTH_)([^\s]+)(_MHZ)/) {
        my $macro = "$1$2$3";
        my $name = $2;
        $name =~ s,_,.,;
        $name *= 1000000;

        $fe_bw{$macro} = $name;
      } elsif (m/(BANDWIDTH_)([^\s,=]+)/) {
        my $macro = "$1$2$3";
        my $name = 0;

        $fe_bw{$macro} = $name;
      }
    }
    #
    # Mode FE_GINTERVAL
    #
<<<<<<< HEAD
<<<<<<< HEAD
    if (m/enum fe_guard_interval \{/) {
=======
    if (m/typedef enum fe_guard_interval \{/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
    if (m/typedef enum fe_guard_interval \{/) {
=======
    if (m/enum fe_guard_interval \{/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
      $mode = FE_GINTERVAL;
      next;
    }
    if ($mode == FE_GINTERVAL) {
<<<<<<< HEAD
<<<<<<< HEAD
      if (m/\};/) {
=======
      if (m/\} fe_guard_interval_t;/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
      if (m/\} fe_guard_interval_t;/) {
=======
      if (m/\};/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
        $mode = NORMAL;
        next;
      }
      if (m/(GUARD_INTERVAL_)([^\s,=]+)/) {
        my $macro = "$1$2";
        my $name = $2;
        $name =~ s,_,/,;

        $fe_guard_interval{$macro} = $name;
      }
    }
    #
    # Mode FE_HIERARCHY
    #
<<<<<<< HEAD
<<<<<<< HEAD
    if (m/enum fe_hierarchy \{/) {
=======
    if (m/typedef enum fe_hierarchy \{/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
    if (m/typedef enum fe_hierarchy \{/) {
=======
    if (m/enum fe_hierarchy \{/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
      $mode = FE_HIERARCHY;
      next;
    }
    if ($mode == FE_HIERARCHY) {
<<<<<<< HEAD
<<<<<<< HEAD
      if (m/\};/) {
=======
      if (m/\} fe_hierarchy_t;/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
      if (m/\} fe_hierarchy_t;/) {
=======
      if (m/\};/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
        $mode = NORMAL;
        next;
      }
      if (m/(HIERARCHY_)([^\s,=]+)/) {
        my $macro = "$1$2";
        my $name = $2;
        $name =~ s,_,/,;

        $fe_hierarchy{$macro} = $name;
      }
    }
    #
    # Mode FE_VOLTAGE
    #
<<<<<<< HEAD
<<<<<<< HEAD
    if (m/enum fe_sec_voltage \{/) {
=======
    if (m/typedef enum fe_sec_voltage \{/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
    if (m/typedef enum fe_sec_voltage \{/) {
=======
    if (m/enum fe_sec_voltage \{/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
      $mode = FE_VOLTAGE;
      next;
    }
    if ($mode == FE_VOLTAGE) {
<<<<<<< HEAD
<<<<<<< HEAD
      if (m/\};/) {
=======
      if (m/\} fe_sec_voltage_t;/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
      if (m/\} fe_sec_voltage_t;/) {
=======
      if (m/\};/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
        $mode = NORMAL;
        next;
      }
      if (m/(SEC_VOLTAGE_)([^\s,]+)/) {
        my $macro = "$1$2";
        my $name = $2;
        $name =~ s,_,/,;

        $fe_voltage{$macro} = $name;
      }
    }
    #
    # Mode FE_TONE
    #
<<<<<<< HEAD
<<<<<<< HEAD
    if (m/enum fe_sec_tone_mode \{/) {
=======
    if (m/typedef enum fe_sec_tone_mode \{/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
    if (m/typedef enum fe_sec_tone_mode \{/) {
=======
    if (m/enum fe_sec_tone_mode \{/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
      $mode = FE_TONE;
      next;
    }
    if ($mode == FE_TONE) {
<<<<<<< HEAD
<<<<<<< HEAD
      if (m/\};/) {
=======
      if (m/\} fe_sec_tone_mode_t;/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
      if (m/\} fe_sec_tone_mode_t;/) {
=======
      if (m/\};/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
        $mode = NORMAL;
        next;
      }
      if (m/(SEC_TONE_)([^\s,]+)/) {
        my $macro = "$1$2";
        my $name = $2;
        $name =~ s,_,/,;

        $fe_tone{$macro} = $name;
      }
    }
    #
    # Mode FE_INVERSION
    #
<<<<<<< HEAD
<<<<<<< HEAD
    if (m/enum fe_spectral_inversion \{/) {
=======
    if (m/typedef enum fe_spectral_inversion \{/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
    if (m/typedef enum fe_spectral_inversion \{/) {
=======
    if (m/enum fe_spectral_inversion \{/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
      $mode = FE_INVERSION;
      next;
    }
    if ($mode == FE_INVERSION) {
<<<<<<< HEAD
<<<<<<< HEAD
      if (m/\};/) {
=======
      if (m/\} fe_spectral_inversion_t;/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
      if (m/\} fe_spectral_inversion_t;/) {
=======
      if (m/\};/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
        $mode = NORMAL;
        next;
      }
      if (m/(INVERSION_)([^\s,]+)/) {
        my $macro = "$1$2";
        my $name = $2;
        $name =~ s,_,/,;

        $fe_inversion{$macro} = $name;
      }
    }
    #
    # Mode FE_PILOT
    #
<<<<<<< HEAD
<<<<<<< HEAD
    if (m/enum fe_pilot \{/) {
=======
    if (m/typedef enum fe_pilot \{/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
    if (m/typedef enum fe_pilot \{/) {
=======
    if (m/enum fe_pilot \{/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
      $mode = FE_PILOT;
      next;
    }
    if ($mode == FE_PILOT) {
<<<<<<< HEAD
<<<<<<< HEAD
      if (m/\};/) {
=======
      if (m/\} fe_pilot_t;/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
      if (m/\} fe_pilot_t;/) {
=======
      if (m/\};/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
        $mode = NORMAL;
        next;
      }
      if (m/(PILOT_)([^\s,]+)/) {
        my $macro = "$1$2";
        my $name = $2;
        $name =~ s,_,/,;

        $fe_pilot{$macro} = $name;
      }
    }
    #
    # Mode FE_ROLLOFF
    #
<<<<<<< HEAD
<<<<<<< HEAD
    if (m/enum fe_rolloff \{/) {
=======
    if (m/typedef enum fe_rolloff \{/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
    if (m/typedef enum fe_rolloff \{/) {
=======
    if (m/enum fe_rolloff \{/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
      $mode =FE_ROLLOFF;
      next;
    }
    if ($mode == FE_ROLLOFF) {
<<<<<<< HEAD
<<<<<<< HEAD
      if (m/\};/) {
=======
      if (m/\} fe_rolloff_t;/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
      if (m/\} fe_rolloff_t;/) {
=======
      if (m/\};/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
        $mode = NORMAL;
        next;
      }
      if (m/(ROLLOFF_)([^\s,]+)/) {
        my $macro = "$1$2";
        my $name = $2;
        $name =~ s,_,/,;

        $fe_rolloff{$macro} = $name;
      }
    }
    #
    # DTV macros
    #
    if (m/\#define\s+(DTV_)([^\s]+)\s+\d+/) {
      next if ($2 eq "IOCTL_MAX_MSGS");

      my $macro = "$1$2";
      my $name = $2;
      $dvb_v5{$macro} = $name;
    }
    #
    # Mode FE_DTS
    #
<<<<<<< HEAD
<<<<<<< HEAD
    if (m/enum fe_delivery_system \{/) {
=======
    if (m/typedef enum fe_delivery_system \{/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
    if (m/typedef enum fe_delivery_system \{/) {
=======
    if (m/enum fe_delivery_system \{/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
      $mode = FE_DTS;
      next;
    }
    if ($mode == FE_DTS) {
<<<<<<< HEAD
<<<<<<< HEAD
      if (m/\};/) {
=======
      if (m/\} fe_delivery_system_t;/) {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
      if (m/\} fe_delivery_system_t;/) {
=======
      if (m/\};/) {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
        $mode = NORMAL;
        next;
      }
      if (m/(SYS_)([^\s,=]+)/) {
        my $macro = "$1$2";
        my $name = $2;
        $name =~ s,_,/,;

        $fe_delivery_system{$macro} = $name;
      }
    }
  }

  close IN;
}

sub sort_func {
  my $aa = $a;
  my $bb = $b;

  my $str_a;
  my $str_b;

  while ($aa && $bb) {
    # Strings before a number
    if ($aa =~ /^([^\d]+)\d/) { $str_a = $1 } else { $str_a = "" };
    if ($bb =~ /^([^\d]+)\d/) { $str_b = $1 } else { $str_b = "" };
    if ($str_a && $str_b) {
      my $cmp = $str_a cmp $str_b;

      return $cmp if ($cmp);

      $aa =~ s/^($str_a)//;
      $bb =~ s/^($str_b)//;
      next;
    }

    # Numbers
    if ($aa =~ /^(\d+)/) { $str_a = $1 } else { $str_a = "" };
    if ($bb =~ /^(\d+)/) { $str_b = $1 } else { $str_b = "" };
    if ($str_a && $str_b) {
      my $cmp = $str_a <=> $str_b;

      return $cmp if ($cmp);

      $aa =~ s/^($str_a)//;
      $bb =~ s/^($str_b)//;
      next;
    }
    last;
  }

  return $a cmp $b;
}

sub output_arrays($$$$$)
{
  my $name = shift;
  my $struct = shift;
  my $type = shift;
  my $bitmap = shift;
  my $decl = shift;

  my $size = keys(%$struct);
  my $max;

  return if (%$struct == 0);

  $type .= " " if (!($type =~ m/\*$/));

  if ($bitmap) {
    printf OUT "struct %s", $name;
    if ($decl) {
      printf OUT " {\n\t\%s idx;\n\tchar *name;\n}", $type;
    }
    if ($decl) {
      printf OUT ";\nextern struct %s", $name;
    }
    printf OUT " %s[%i]", $name, $size;
  } else {
    printf OUT "const %s%s[%i]", $type, $name, $size + 1;
  }

  if ($decl) {
    printf OUT ";\n";
  } else {
    printf OUT " = {\n";

    foreach my $i (sort keys %$struct) {
      my $len = length($i);
      $max = $len if ($len > $max);
    }

    foreach my $i (sort sort_func keys %$struct) {
      if ($bitmap) {
        printf OUT "\t{ %s, ", $i;
      } else {
        printf OUT "\t[%s] = ", $i;
      }
      my $len = length($i);
      while ($len < $max) {
        print OUT " ";
        $len++;
      }
      if ($bitmap) {
        printf OUT "\"%s\" },\n", $struct->{$i};
      } else {
        if ($type eq "char *") {
          printf OUT "\"%s\",\n", $struct->{$i};
        } else {
          printf OUT "%s,\n", $struct->{$i};
        }
      }
    }

    if (!$bitmap) {
      printf OUT "\t[%s] = ", $size;
      if ($type eq "char *") {
        printf OUT "NULL,\n";
      } else {
        printf OUT "0,\n";
      }
    }


    printf OUT "};\n\n";
  }
}

<<<<<<< HEAD
<<<<<<< HEAD
my $fe_file = "$dir/linux/dvb/frontend.h";
=======
my $fe_file = "$dir/uapi/linux/dvb/frontend.h";
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
my $fe_file = "$dir/uapi/linux/dvb/frontend.h";
=======
my $fe_file = "$dir/linux/dvb/frontend.h";
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

copy $fe_file, "../include/dvb-frontend.h";

# Generate a header file with the API conversions
open OUT, ">dvb-v5.h" or die "Can't write on dvb-v5.h";
gen_fe $fe_file;
print OUT <<EOF;
/*
 * File auto-generated from the kernel sources. Please, don't edit it
 */
#ifndef _DVB_V5_CONSTS_H
#define _DVB_V5_CONSTS_H
#include <libdvbv5/dvb-frontend.h>
EOF
output_arrays ("fe_caps_name", \%fe_caps, "unsigned", 1, 1);
output_arrays ("fe_status_name", \%fe_status, "unsigned", 1, 1);
output_arrays ("fe_code_rate_name", \%fe_code_rate, "char *", 0, 1);
output_arrays ("fe_modulation_name", \%fe_modulation, "char *", 0, 1);
output_arrays ("fe_transmission_mode_name", \%fe_t_mode, "char *", 0, 1);
output_arrays ("fe_bandwidth_name", \%fe_bw, "unsigned", 0, 1);
output_arrays ("fe_guard_interval_name", \%fe_guard_interval, "char *", 0, 1);
output_arrays ("fe_hierarchy_name", \%fe_hierarchy, "char *", 0, 1);
output_arrays ("fe_voltage_name", \%fe_voltage, "char *", 0, 1);
output_arrays ("fe_tone_name", \%fe_tone, "char *", 0, 1);
output_arrays ("fe_inversion_name", \%fe_inversion, "char *", 0, 1);
output_arrays ("fe_pilot_name", \%fe_pilot, "char *", 0, 1);
output_arrays ("fe_rolloff_name", \%fe_rolloff, "char *", 0, 1);
output_arrays ("dvb_v5_name", \%dvb_v5, "char *", 0, 1);
output_arrays ("delivery_system_name", \%fe_delivery_system, "char *", 0, 1);
printf OUT "#endif\n";

close OUT;

# Generate a source file with the API conversions
open OUT, ">dvb-v5.c" or die "Can't write on dvb-v5.c";
print OUT <<EOF;
/*
 * File auto-generated from the kernel sources. Please, don't edit it
 */
#include <stddef.h>

<<<<<<< HEAD
<<<<<<< HEAD
#include "dvb-v5.h"
=======
#include <libdvbv5/dvb-v5.h>
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
#include <libdvbv5/dvb-v5.h>
=======
#include "dvb-v5.h"
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

EOF
output_arrays ("fe_caps_name", \%fe_caps, "unsigned", 1, 0);
output_arrays ("fe_status_name", \%fe_status, "unsigned", 1, 0);
output_arrays ("fe_code_rate_name", \%fe_code_rate, "char *", 0, 0);
output_arrays ("fe_modulation_name", \%fe_modulation, "char *", 0, 0);
output_arrays ("fe_transmission_mode_name", \%fe_t_mode, "char *", 0, 0);
output_arrays ("fe_bandwidth_name", \%fe_bw, "unsigned", 0, 0);
output_arrays ("fe_guard_interval_name", \%fe_guard_interval, "char *", 0, 0);
output_arrays ("fe_hierarchy_name", \%fe_hierarchy, "char *", 0, 0);
output_arrays ("fe_voltage_name", \%fe_voltage, "char *", 0, 0);
output_arrays ("fe_tone_name", \%fe_tone, "char *", 0, 0);
output_arrays ("fe_inversion_name", \%fe_inversion, "char *", 0, 0);
output_arrays ("fe_pilot_name", \%fe_pilot, "char *", 0, 0);
output_arrays ("fe_rolloff_name", \%fe_rolloff, "char *", 0, 0);
output_arrays ("dvb_v5_name", \%dvb_v5, "char *", 0, 0);
output_arrays ("delivery_system_name", \%fe_delivery_system, "char *", 0, 0);

close OUT;
