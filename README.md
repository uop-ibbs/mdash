# mdash

MDASH is a program for identifying major conformational states in
molecular dynamics simulations, based on the distributions of key
dihedral angles. It was developed originally in the Centre for
Molecular Design at the University of Portsmouth.

The algorithm was first described in Salt *et al*.[1] and has been used
recently to analyse trajectories of the cyclic peptides arginine
vasopressin[2] and urotensin[3].

The software is distributed under the terms of the GNU General Public
License (see the file [LICENSE](LICENSE) for details).

The [latest release](http://github.com/uop-ibbs/mdash/releases/latest)
is a maintenance release to enable MDASH to be built with the latest
versions of its third-party dependencies. There are no substantive
changes to the software itself. Binary packages for the major
GNU/Linux distributions are provided at the
[openSUSE Build Service](https://software.opensuse.org/download.html?project=home%3Adcwhitley&package=mdash).
A Windows installer is provided with the
[previous release](http://github.com/uop-ibbs/mdash/releases/tag/v3.1.0).
See [INSTALL.md](INSTALL.md) for further details and instructions on
compiling the program from the source code.

### A change of name

The program was originally called `dash` but since its first release,
the Debian Almquist shell, also named `dash`, has become the default
shell on Debian-based distributions such as Ubuntu. To avoid a name
clash, this release has been renamed MDASH and the main program is now
`mdash`. The algorithm, however, will continue to be known as the DASH
algorithm.

### References

[1]: D. W. Salt, B. D. Hudson, L. Banting, M. J. Ellis and M. G. Ford.
DASH: A novel analysis method for molecular dynamics simulation data. Analysis of ligands of PPAR-&gamma;.
J. Med. Chem. 2005, **48**, 3214-3220. [doi:10.1021/jm049216s](http://pubs.acs.org/doi/abs/10.1021/jm049216s)

[2]: E. Haensele, L. Banting, D. C. Whitley and T. Clark.
Conformation and dynamics of 8-Arg-vasopressin in solution.
J. Mol. Model. 2014, **20**, 2485. [doi:10.1007/s00894-014-2485-0](https://doi.org/10.1007/s00894-014-2485-0)

[3]: E. Haensele, N. Mele, M. Miljak, C. M. Read, D. C. Whitley, L. Banting, C. Del&eacute;p&eacute;e, J. Sopkova-de Oliveira Santos, A. Lepailleur, R. Bureau, J. W. Essex and T. Clark.
Conformation and Dynamics of Human Urotensin II and Urotensin Related Peptide in Aqueous Solution.
J. Chem. Inf. Model. 2017, **57**, 298-310. [doi:10.1021/acs.jcim.6b00706](http://dx.doi.org/10.1021/acs.jcim.6b00706)
