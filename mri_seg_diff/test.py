#!/usr/bin/env python
import os
import sys, os.path as op
sys.path.append(op.join(op.dirname(sys.argv[0]), '../python'))
import freesurfer.test as fst

rt = fst.RegressionTest()

# should be <abspath>/testdata
subjects_dir = os.getcwd() + "/testdata"
os.environ["SUBJECTS_DIR"] = subjects_dir

home = os.environ.get("HOME")
home_license = home + "/" + "license.txt"
if op.isfile(home_license) and not os.environ.get("FS_LICENSE"):
   os.environ["FS_LICENSE"] = home_license
   # print "FS_LICENSE = %s" % (os.environ["FS_LICENSE"])
# print "SUBJECTS_DIR = %s" % (os.environ["SUBJECTS_DIR"])

# this command apparently expects the license file to be found as ../distribution/license.txt
license = os.environ.get("FS_LICENSE")
license_dest = "../distribution/"
license_dest_file = license_dest + "license.txt"
if op.isfile(license) and not os.access(license_dest_file,os.R_OK):
   # cmd = "(cd " + license_dest + " && sudo ln -s " + license + " " + "license.txt)"
   cmd = "(cd " + license_dest + " && ln -s " + license + " " + "license.txt)"
   os.system(cmd)
   os.system("ls -l " + license_dest_file)

# mri_seg_diff --debug --seg1 /Applications/freesurfer/subjects/bert/mri/aseg.auto.mgz --seg2 /Applications/freesurfer/subjects/bert/mri/aseg.mgz --diff /tmp/test/mri_seg_diff/aseg_diff_out.mgz

cmd = "mri_seg_diff --debug --seg1 " + subjects_dir + "/mri/aseg.auto.mgz --seg2 " + subjects_dir + "/mri/aseg.mgz " + "--diff " + subjects_dir + "/aseg_diff_out.mgz"
# print "cmd = %s" % cmd

rt.run(cmd)

f_out = subjects_dir + "/" + "aseg_diff_out.mgz"
f_ref = subjects_dir + "/" + "aseg_diff_ref.mgz" 

rt.mridiff(f_out,f_ref)

rt.cleanup()

