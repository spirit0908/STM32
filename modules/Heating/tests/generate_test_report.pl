#!/usr/bin/perl

# Check number of arguments:
$num_args = $#ARGV + 1;
if ($num_args == 2 ) {
    $input_file=$ARGV[0];		# input file (log)
    $output_file=$ARGV[1];		# output file (xml)
}
elsif ($num_args == 3 ) {
    if( $ARGV[0] == "-list" ){
        $input_file=$ARGV[1];		# input file (log)
        $output_file=$ARGV[2];		# output file (xml)
    }
    else{
        print "\nUsage: generate_xml_report.pl -list <input_list_file> <output_xml_file>\n";
    }
}
else {
    print "\nUsage: generate_xml_report.pl <input_log_file> <output_xml_file>\n";
    exit;
}



open(INPUT_FILE,$input_file) or die "$input_file not found!";
open(OUTPUT_FILE,">".$output_file) or die "$output_file not writeable!";

# Initialize result file:
print OUTPUT_FILE "\<\?xml version=\"1.0\"\?\>"."\n\<span>\n";

print "\n";

$nbPassed=0;
$nbFailed=0;
$nbNotrun=0;

while (<INPUT_FILE>)
{
    $line = $_;

    if ($line =~ m/^Module\: (.*)/)
    {
        #$TestModule = $1;
        print OUTPUT_FILE "  <testModule>\n";
        print OUTPUT_FILE "    <moduleName>".$1."</moduleName>"."\n";
    }
    elsif ($line =~ m/^\[([xvu])\] TEST (.*):/)
    {
        print OUTPUT_FILE "    <testResult>\n";
        print OUTPUT_FILE "      <testname>".$2."</testname>\n";
        
        if($1 eq "v")
        {
            $nbPassed++;
            print OUTPUT_FILE "      <teststatus>passed</teststatus>\n";
        }
        elsif($1 eq "x")
        {
            $nbFailed++;
            print OUTPUT_FILE "      <teststatus>failed</teststatus>\n";
        }
        else
        {
            $nbNotrun++;
            print OUTPUT_FILE "      <teststatus>notrun</teststatus>\n";
        }

        print OUTPUT_FILE "    </testResult>\n";
    }
}

$nbTotal = $nbPassed+$nbFailed+$nbNotrun;
$percentPassed = int( ($nbPassed*100) / $nbTotal);

print OUTPUT_FILE "    <nbPass>".$nbPassed."</nbPass>\n";
print OUTPUT_FILE "    <nbFail>".$nbFailed."</nbFail>\n";
print OUTPUT_FILE "    <nbNotrun>".$nbNotrun."</nbNotrun>\n";
print OUTPUT_FILE "    <nbTotal>".($nbPassed+$nbFailed+$nbNotrun)."</nbTotal>\n";
print OUTPUT_FILE "    <percentPassed>".$percentPassed."</percentPassed>\n";

print OUTPUT_FILE "  </testModule>\n";
print OUTPUT_FILE "</span>\n";

close(INPUT_FILE);
close(OUTPUT_FILE);
