mm2.c

(dev) ➜  PA_3_handout git:(master) ✗ make
make: 'mdriver' is up to date.
(dev) ➜  PA_3_handout git:(master) ✗ OIFS="${IFS}"
(dev) ➜  PA_3_handout git:(master) ✗ IFS=" "
(dev) ➜  PA_3_handout git:(master) ✗ for i in $(echo "short1-bal.rep short2-bal.rep short3-bal.rep binary-bal.rep cp-decl-bal.rep random-bal.rep realloc-bal.rep");
for> do
for> echo "----------------- Working on ${i} -----------------"
for> ./mdriver2 -V -f "traces/${i}"
for> done
----------------- Working on short1-bal.rep -----------------
Team Name:team name
Member 1 :Fenil Mehta:fenilgmehta@cse.iitb.ac.in
Member 2 :Vipin Mahawar:member_2@cse.iitb.ac.in
Measuring performance with gettimeofday().

Testing mm malloc
Reading tracefile: traces/short1-bal.rep
Checking mm_malloc for correctness, efficiency, and performance.

Results for mm malloc:
trace  valid  util     ops      secs      Kops
 0       yes   99%      12  0.000000     30000
Total          99%      12  0.000000     30000

Perf index = 60 (util) + 40 (thru) = 100/100
----------------- Working on short2-bal.rep -----------------
Team Name:team name
Member 1 :Fenil Mehta:fenilgmehta@cse.iitb.ac.in
Member 2 :Vipin Mahawar:member_2@cse.iitb.ac.in
Measuring performance with gettimeofday().

Testing mm malloc
Reading tracefile: traces/short2-bal.rep
Checking mm_malloc for correctness, efficiency, and performance.

Results for mm malloc:
trace  valid  util     ops      secs      Kops
 0       yes   99%      12  0.000000     30000
Total          99%      12  0.000000     30000

Perf index = 60 (util) + 40 (thru) = 100/100
----------------- Working on short3-bal.rep -----------------
Team Name:team name
Member 1 :Fenil Mehta:fenilgmehta@cse.iitb.ac.in
Member 2 :Vipin Mahawar:member_2@cse.iitb.ac.in
Measuring performance with gettimeofday().

Testing mm malloc
Reading tracefile: traces/short3-bal.rep
Checking mm_malloc for correctness, efficiency, and performance.

Results for mm malloc:
trace  valid  util     ops      secs      Kops
 0       yes   50%      10  0.000000     33333
Total          50%      10  0.000000     33333

Perf index = 30 (util) + 40 (thru) = 70/100
----------------- Working on binary-bal.rep -----------------
Team Name:team name
Member 1 :Fenil Mehta:fenilgmehta@cse.iitb.ac.in
Member 2 :Vipin Mahawar:member_2@cse.iitb.ac.in
Measuring performance with gettimeofday().

Testing mm malloc
Reading tracefile: traces/binary-bal.rep
Checking mm_malloc for correctness, efficiency, and performance.

Results for mm malloc:
trace  valid  util     ops      secs      Kops
 0       yes   54%   12000  0.075110       160
Total          54%   12000  0.075110       160

Perf index = 32 (util) + 11 (thru) = 43/100
----------------- Working on cp-decl-bal.rep -----------------
Team Name:team name
Member 1 :Fenil Mehta:fenilgmehta@cse.iitb.ac.in
Member 2 :Vipin Mahawar:member_2@cse.iitb.ac.in
Measuring performance with gettimeofday().

Testing mm malloc
Reading tracefile: traces/cp-decl-bal.rep
Checking mm_malloc for correctness, efficiency, and performance.

Results for mm malloc:
trace  valid  util     ops      secs      Kops
 0       yes   99%    6648  0.000493     13479
Total          99%    6648  0.000493     13479

Perf index = 59 (util) + 40 (thru) = 99/100
----------------- Working on random-bal.rep -----------------
Team Name:team name
Member 1 :Fenil Mehta:fenilgmehta@cse.iitb.ac.in
Member 2 :Vipin Mahawar:member_2@cse.iitb.ac.in
Measuring performance with gettimeofday().

Testing mm malloc
Reading tracefile: traces/random-bal.rep
Checking mm_malloc for correctness, efficiency, and performance.

Results for mm malloc:
trace  valid  util     ops      secs      Kops
 0       yes   94%    4800  0.005810       826
Total          94%    4800  0.005810       826

Perf index = 57 (util) + 40 (thru) = 97/100
----------------- Working on realloc-bal.rep -----------------
Team Name:team name
Member 1 :Fenil Mehta:fenilgmehta@cse.iitb.ac.in
Member 2 :Vipin Mahawar:member_2@cse.iitb.ac.in
Measuring performance with gettimeofday().

Testing mm malloc
Reading tracefile: traces/realloc-bal.rep
Checking mm_malloc for correctness, ERROR [trace 0, line 10]: Payload (0xf6961250:0xf696154f) lies outside heap (0xf6961010:0xf696153f)

Results for mm malloc:
trace  valid  util     ops      secs      Kops
 0        no     -       -         -         -
Total            -       -         -         -

Terminated with 1 errors
(dev) ➜  PA_3_handout git:(master) ✗ IFS="${OIFS}"
(dev) ➜  PA_3_handout git:(master) ✗ 
