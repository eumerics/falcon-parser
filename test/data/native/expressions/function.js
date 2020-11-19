//- contextual_identifier
!function* yield(){}; //? <-> @1:12
!function*(){ yield.a; }; //? <-> @1:20 -default
!function*(){ var yield; }; //? <-> @1:19
!function*(){ let yield; }; //? <-> @1:19
!function*(){ yield: }; //? <-> @1:15
///
!async function await(){}; //? <-> @1:17
!async function(){ await.a; }; //? <-> @1:25 -default
!async function(){ var await; }; //? <-> @1:24
!async function(){ let await; }; //? <-> @1:24
!async function(){ await: }; //? <-> @1:20
///
!async function* yield(){}; //? <-> @1:18
!async function*(){ yield.a; }; //? <-> @1:26 -default
!async function*(){ var yield; }; //? <-> @1:25
!async function*(){ let yield; }; //? <-> @1:25
!async function*(){ yield: }; //? <-> @1:21
///
!async function* await(){}; //? <-> @1:18
!async function*(){ await.a; }; //? <-> @1:26 -default
!async function*(){ var await; }; //? <-> @1:25
!async function*(){ let await; }; //? <-> @1:25
!async function*(){ await: }; //? <-> @1:21
