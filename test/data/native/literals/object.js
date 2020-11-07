/// class early errors that are not applicable to object literals
!{ constructor(){}, constructor(){} } //? <+>
!{ * constructor(){} } //? <+>
!{ async constructor(){} } //? <+>
!{ async* constructor(){} } //? <+>
!{ get constructor(){} } //? <+>
!{ set constructor(b){} } //? <+>
