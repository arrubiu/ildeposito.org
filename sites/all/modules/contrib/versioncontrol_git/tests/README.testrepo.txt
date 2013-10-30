In order to adequately test repository interaction logic, versioncontrol_git
includes a test repository - testrepo.tar.gz, in this directory. As many
instances of this repository can be set up and torn down as part of the test
running process as are required, a process that is automated through the
VersioncontrolGitTestCase::versioncontrolCreateRepoFromTestRepo() method.

In order to ease working with this repository, this file contains reference
information about the exact state of the compressed test repository. You could
also just extract a copy of the repository yourself, but by referring to this
static file, you can be sure you haven't inadvertently changed anything in your
own repo, and are therefore working from an altered state.

Should any changes to the test repository need to be made, it is therefore
ABSOLUTELY ESSENTIAL that this file be updated accordingly!

====

$ git show-ref -d --heads --tags
28e2c35b6f7626d662ffda2c344a782e639f76e7 refs/heads/enhancements
3b225dfda13090853f744cc1209f392442a6ab13 refs/heads/feature
82add9c8b2f9740874192cec11737221d9691812 refs/heads/fixes
0f0280aefe4d0c3384cb04a0bbb15c9543f46a69 refs/heads/master
3a8d2b09b2b33baf58b56273e51f0005853c65cc refs/tags/annotated
b1e97e0f979c5e3580942b335e85bf17c3216397 refs/tags/annotated^{}
f33712b2039d8a938c9269269a2d0b463d8994e3 refs/tags/signed
b1e97e0f979c5e3580942b335e85bf17c3216397 refs/tags/signed^{}
b1e97e0f979c5e3580942b335e85bf17c3216397 refs/tags/simple

$ cat HEAD
ref: refs/heads/master

$ cat packed-refs 
# pack-refs with: peeled 
28e2c35b6f7626d662ffda2c344a782e639f76e7 refs/heads/enhancements
3b225dfda13090853f744cc1209f392442a6ab13 refs/heads/feature
82add9c8b2f9740874192cec11737221d9691812 refs/heads/fixes
0f0280aefe4d0c3384cb04a0bbb15c9543f46a69 refs/heads/master
3a8d2b09b2b33baf58b56273e51f0005853c65cc refs/tags/annotated
^b1e97e0f979c5e3580942b335e85bf17c3216397
f33712b2039d8a938c9269269a2d0b463d8994e3 refs/tags/signed
^b1e97e0f979c5e3580942b335e85bf17c3216397
b1e97e0f979c5e3580942b335e85bf17c3216397 refs/tags/simple

$ git rev-list master
0f0280aefe4d0c3384cb04a0bbb15c9543f46a69
550a5fb5628901ad6f0a7f933c87ed7570541484
0e49a5e0ea64c1874bf476da473451f567b7e108
06ed7cc29f4afd3473b3905cc8dce6471b963e5a
28e2c35b6f7626d662ffda2c344a782e639f76e7
82add9c8b2f9740874192cec11737221d9691812
e5499e3bb2f09f2141f084f6099e81f01acbcb73
7d5e9ebb5f647f8097323468c671176c154e2f5e
30e1782942b8b0edcd0225b8045bbfb6743b7318
3b225dfda13090853f744cc1209f392442a6ab13
f447cfa0fb27f83e1f19ca526ab0c8393111b491
0ae347f2660d32bee29ef144b681fa070c3c1c1c
1c769276b795ac63eee65341151f65b0ee5acf59
61dda575c87a2bd1553f4b503370b724b432d64e
b1e97e0f979c5e3580942b335e85bf17c3216397
4817efad5041c7ce8de84fb1013d859eec5231d6

$ git rev-list fixes
82add9c8b2f9740874192cec11737221d9691812
e5499e3bb2f09f2141f084f6099e81f01acbcb73
7d5e9ebb5f647f8097323468c671176c154e2f5e
30e1782942b8b0edcd0225b8045bbfb6743b7318
3b225dfda13090853f744cc1209f392442a6ab13
f447cfa0fb27f83e1f19ca526ab0c8393111b491
0ae347f2660d32bee29ef144b681fa070c3c1c1c
1c769276b795ac63eee65341151f65b0ee5acf59
61dda575c87a2bd1553f4b503370b724b432d64e
b1e97e0f979c5e3580942b335e85bf17c3216397
4817efad5041c7ce8de84fb1013d859eec5231d6

$ git rev-list enhancements
28e2c35b6f7626d662ffda2c344a782e639f76e7
e5499e3bb2f09f2141f084f6099e81f01acbcb73
7d5e9ebb5f647f8097323468c671176c154e2f5e
30e1782942b8b0edcd0225b8045bbfb6743b7318
3b225dfda13090853f744cc1209f392442a6ab13
f447cfa0fb27f83e1f19ca526ab0c8393111b491
0ae347f2660d32bee29ef144b681fa070c3c1c1c
1c769276b795ac63eee65341151f65b0ee5acf59
61dda575c87a2bd1553f4b503370b724b432d64e
b1e97e0f979c5e3580942b335e85bf17c3216397
4817efad5041c7ce8de84fb1013d859eec5231d6

$ git rev-list feature
3b225dfda13090853f744cc1209f392442a6ab13
f447cfa0fb27f83e1f19ca526ab0c8393111b491
0ae347f2660d32bee29ef144b681fa070c3c1c1c
1c769276b795ac63eee65341151f65b0ee5acf59
61dda575c87a2bd1553f4b503370b724b432d64e
b1e97e0f979c5e3580942b335e85bf17c3216397
4817efad5041c7ce8de84fb1013d859eec5231d6

$ git log --oneline --graph --all --decorate
 * 0f0280a (HEAD, master) Another commit by other user.
 * 550a5fb another user commit
 *-.   0e49a5e Merge branches 'fixes' and 'enhancements'
 |\ \
 | | * 28e2c35 (enhancements) una linea mas
 | * | 82add9c (fixes) una linea mas
 | |/
 * | 06ed7cc otra linea de emergencia
 |/
 * e5499e3 moviendo un archivo
 *   7d5e9eb Merge branch 'feature'
 |\
 | * 3b225df (feature) otra linea mas
 | * f447cfa una linea mas
 * | 30e1782 commit independiente a feature
 |/
 * 0ae347f otr commit a dos archivos
 * 1c76927 otro commit con issue #1234
 * 61dda57 agregar un folder
 * b1e97e0 (tag: simple, tag: signed, tag: annotated) algo de contenido 2
 * 4817efa inicial
