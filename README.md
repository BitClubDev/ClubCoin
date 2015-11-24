
ClubCoin development tree

ClubCoin is a PoS-based cryptocurrency forked from BlackCoin.

Resetting the blockchain
========================

For development purposes or experimentation, the blockchain can be reset,
restarted and pre-mined by following these steps:

* Stop all nodes - servers, clients, mobile, etc. The alternative is to
  generate a new genesis block, which isn't hard but isn't plug & play also.
* Remove the servers' data directories. The Ansible playbook named
  `reset-ccnodes.yml` can be used to do that while installing new root
  nodes.
* Start the servers with empty databases.
* Mine 402 blocks in PoW, doesn't matter where or how.
* Transfer some coins so that all server nodes have some money they can use
  for staking. The idea is for the staking to start as soon as possible on
  as large number of nodes as possible. An example number of coins is
  100,000.
* Continue mining PoW for at least 1 hour for the transferred coins from the
  previous steps become mature for staking and that staking starts on all nodes.
* Stop PoW mining at some point.
* If this is to be the production chain, make this point in blockchain a
  checkpoint (see `checkpoints.cpp`).

Parameters such as the PoW block reward, the maturity for mined blocks (101
blocks) and for staking (1 hour) are all hard-coded in the executables.


Development process
===================

Developers work in their own trees, then submit pull requests when
they think their feature or bug fix is ready.

The patch will be accepted if there is broad consensus that it is a
good thing.  Developers should expect to rework and resubmit patches
if they don't match the project's coding conventions (see coding.txt)
or are controversial.

The master branch is regularly built and tested, but is not guaranteed
to be completely stable. Tags are regularly created to indicate new
stable release versions of ClubCoin.

Feature branches are created when there are major new features being
worked on by several people.

From time to time a pull request will become outdated. If this occurs, and
the pull is no longer automatically mergeable; a comment on the pull will
be used to issue a warning of closure. The pull will be closed 15 days
after the warning if action is not taken by the author. Pull requests closed
in this manner will have their corresponding issue labeled 'stagnant'.

Issues with no commits will be given a similar warning, and closed after
15 days from their last activity. Issues closed in this manner will be 
labeled 'stale'.

