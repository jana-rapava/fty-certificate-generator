# fty-template

This is just a template for agent repository 

## How to create your agent

To reate your agent, you have to specify this template when creating a repo on gitbub.

Then you have to update the project.xml file and run from the local clone of your repo the tools ProjectXML from the repo FTY

```bash
../FTY/ProjectXML -A --kill-cmake
```

Then you can add all the file needed: Example with generation of the template:

```bash
	doc/fty-template.adoc
	include/fty_template.h
	include/fty_template_class_example.h
	include/fty_template_library.h
	packaging/debian/fty-template.dsc.obs
	packaging/redhat/fty-template.spec
	src/fty_template_class_example.cc
	src/fty_template_classes.h
	src/fty_template_private_selftest.cc
	src/fty_template_selftest.cc
	src/libfty_template.pc.in
```
