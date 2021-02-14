#Test
test: $(MAIN_OUT_BIN)
	#rm out/tests/*.xml
	# Create folder structure
	mkdir -p out/tests/
	# Generate individual test reports
	(cd modules/Heating/tests; make runtest)
	cp modules/Heating/tests/test_result_Heating.xml out/tests/
	(cd modules/pinCode/tests; make runtest)
	cp modules/pinCode/tests/test_result_pinCode.xml out/tests/
	(cd modules/Teleinfo/tests; make runtest)
	cp modules/Teleinfo/tests/test_result_Teleinfo.xml out/tests/
	# Build test report
	(cd out/tests; ../../tools/test_report_generator/combine_xml.sh test_results.xml)
#	(cd out/tests; xsltproc ../../tools/test_report_generator/test_report_generator.xsl test_results.xml > Test_results.html )

#Execute tests and generate report
testreport: test
	#(cd tools; cp combine_xml.sh ../out/tests/combine_xml.sh)
	#(cd out/tests; ./combine_xml.sh test_results.xml)
	(cd out/tests; xsltproc ../../tools/test_report_generator/test_report_generator.xsl test_results.xml > Test_results.html )
	#(cd out/tests; rm combine_xml.sh)


clean:
	#find . -type f -name '*.o' -delete
	rm out/tests/*.xml
	rm out/tests/*.html

