/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2016 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::incompressible::alphatJayatillekeWallFunctionTemprPrFvPatchScalarField

Group
    grpIcoWallFunctions

Description
    This boundary condition provides a kinematic turbulent thermal conductivity
    for using wall functions, using the Jayatilleke 'P' function.

Usage
    \table
        Property     | Description             | Required    | Default value
        Prt          | turbulent Prandtl number | no         | 0.85
        Cmu          | model coefficient       | no          | 0.09
        kappa        | Von Karman constant     | no          | 0.41
        E            | model coefficient       | no          | 9.8
    \endtable

    Example of the boundary condition specification:
    \verbatim
    <patchName>
    {
        type            alphatJayatillekeWallFunctionTemprPr;
    }
    \endverbatim

Note
    The units of kinematic turbulent thermal conductivity are [m2/s]

See also
    Foam::fixedValueFvPatchField

SourceFiles
    alphatJayatillekeWallFunctionTemprPrFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#ifndef alphatJayatillekeWallFunctionTemprPrFvPatchScalarField_H
#define alphatJayatillekeWallFunctionTemprPrFvPatchScalarField_H

#include "fixedValueFvPatchFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace incompressible
{

/*---------------------------------------------------------------------------*\
       Class alphatJayatillekeWallFunctionTemprPrFvPatchScalarField Declaration
\*---------------------------------------------------------------------------*/

class alphatJayatillekeWallFunctionTemprPrFvPatchScalarField
:
    public fixedValueFvPatchScalarField
{
protected:

    // Protected data

        //- Turbulent Prandtl number
        scalar Prt_;

        //- Cmu coefficient
        scalar Cmu_;

        //- Von Karman constant
        scalar kappa_;

        //- E coefficient
        scalar E_;


        // Solution parameters

            static scalar tolerance_;
            static label maxIters_;


    // Protected member functions

        //- Check the type of the patch
        virtual void checkType();

        //- `P' function
        scalar Psmooth(const scalar Prat) const;

        //- Calculate y+ at the edge of the thermal laminar sublayer
        scalar yPlusTherm
        (
            const scalar P,
            const scalar Prat
        ) const;


public:

    //- Runtime type information
    TypeName("alphatJayatillekeWallFunctionTemprPr");


    // Constructors

        //- Construct from patch and internal field
        alphatJayatillekeWallFunctionTemprPrFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        alphatJayatillekeWallFunctionTemprPrFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //  alphatJayatillekeWallFunctionTemprPrFvPatchScalarField
        //  onto a new patch
        alphatJayatillekeWallFunctionTemprPrFvPatchScalarField
        (
            const alphatJayatillekeWallFunctionTemprPrFvPatchScalarField&,
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        alphatJayatillekeWallFunctionTemprPrFvPatchScalarField
        (
            const alphatJayatillekeWallFunctionTemprPrFvPatchScalarField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchScalarField> clone() const
        {
            return tmp<fvPatchScalarField>
            (
                new alphatJayatillekeWallFunctionTemprPrFvPatchScalarField(*this)
            );
        }

        //- Construct as copy setting internal field reference
        alphatJayatillekeWallFunctionTemprPrFvPatchScalarField
        (
            const alphatJayatillekeWallFunctionTemprPrFvPatchScalarField&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchScalarField> clone
        (
            const DimensionedField<scalar, volMesh>& iF
        ) const
        {
            return tmp<fvPatchScalarField>
            (
                new alphatJayatillekeWallFunctionTemprPrFvPatchScalarField(*this, iF)
            );
        }


    // Member functions

        // Evaluation functions

            //- Update the coefficients associated with the patch field
            virtual void updateCoeffs();


        // I-O

            //- Write
            virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace incompressible
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
