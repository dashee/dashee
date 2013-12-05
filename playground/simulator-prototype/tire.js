// Tire Definition, with Box 2D tutorial style comments.
(function(){
    // Box 2D tire class takes the Box 2D World as a parameter.
    // Requires box 2D.
    var tireDef = function(world){
        var that = {};
        that.m_body;

        // Forward and backward force is applied the maxDriveForce rate
        // until the speed is reached
        that.m_maxForwardSpeed = 7;
        that.m_maxBackwardSpeed = -3;
        that.m_maxDriveForce = .5;

        // Create the box 2D body.
        var bodyDef = new b2BodyDef;

        // Set type to dynamic unlike static default.
        bodyDef.type = b2Body.b2_dynamicBody;
        
        // Add to simulation.
        that.m_body = world.CreateBody(bodyDef);

        var fixDef = new b2FixtureDef;
        fixDef.density = 1.0; // Weight relative to size
        fixDef.friction = 0.5;
        fixDef.restitution = 0.2; // Bouncyness
        fixDef.shape = new b2PolygonShape;

        // The SetAsBox function takes half the width and height
        // So the figures below need to be doubled and it's in meters.
        // 0.0625 is 12.5 cm in width about as small as Box2D supports.
        fixDef.shape.SetAsBox(0.0625, 0.15);
        that.m_body.CreateFixture(fixDef);

        // Velocity to the side.
        function getLateralVelocity() {
            //console.log(that.m_body.GetWorldVector());
            var currentRightNormal = that.m_body.GetWorldVector( new b2Vec2(1,0) );
            //console.log(that.m_body.GetLinearVelocity());
            return b2Math.MulFV(
            b2Math.Dot( currentRightNormal, that.m_body.GetLinearVelocity() ),
            currentRightNormal);
        }

        // Velocity to the 'front.'
        function getForwardVelocity() {
            //console.log(that.m_body.GetWorldVector());
            var currentRightNormal = that.m_body.GetWorldVector( new b2Vec2(0,1) );
            //console.log(that.m_body.GetLinearVelocity());
            return b2Math.MulFV(
            b2Math.Dot( currentRightNormal, that.m_body.GetLinearVelocity() ),
            currentRightNormal);
        }

        that.updateFriction = function() {
            // Kill lateral velocity, optionally allow some to get skid effect.
            var impulse = b2Math.MulFV(that.m_body.GetMass(), getLateralVelocity().GetNegative());
            // 3 becomes maxLateralImpulse and don't use stupid math operators that dont work
            //if ( impulse.Length() > 3 )
            //   impulse *= 3 / impulse.Length();
            that.m_body.ApplyImpulse( impulse, that.m_body.GetWorldCenter() );
            
            // Kill angular velocity
            that.m_body.ApplyAngularImpulse( 0.1 * that.m_body.GetInertia() * -that.m_body.GetAngularVelocity() );

            var currentForwardNormal = getForwardVelocity();
            var currentForwardSpeed = currentForwardNormal.Normalize();
            var dragForceMagnitude = -0.1 * currentForwardSpeed;
            that.m_body.ApplyForce( b2Math.MulFV(dragForceMagnitude , currentForwardNormal), that.m_body.GetWorldCenter() );
        }

        that.updateDrive = function() {
            //find desired speed
            var desiredSpeed = 0;
            if( keys[38] || keys[40]) {
                if(keys[38]){
                    desiredSpeed = that.m_maxForwardSpeed;
                }else{
                    desiredSpeed = that.m_maxBackwardSpeed;
                }
            }else{
                return;
            }
            //find current speed in forward direction
            var currentForwardNormal = that.m_body.GetWorldVector(new b2Vec2(0,1) );
            var currentSpeed = b2Math.Dot( getForwardVelocity(), currentForwardNormal );

            //apply necessary force
            var force = 0;
            if ( desiredSpeed > currentSpeed )
                force = that.m_maxDriveForce;
            else if ( desiredSpeed < currentSpeed )
                force = -that.m_maxDriveForce;
            else
                return;
            that.m_body.ApplyForce(b2Math.MulFV(force , currentForwardNormal), that.m_body.GetWorldCenter() );
        }

        // Function not use except for stand alone tyre testing.
        that.updateTurn = function() {
            var desiredTorque = 0;
            if( keypressed == 'RIGHT' || keypressed == 'LEFT') {
                if(keypressed == 'LEFT'){
                    desiredTorque = -0.1; 
                }else{
                    desiredTorque = 0.1; 
                }
            }else{
                return;
            }
            that.m_body.ApplyTorque( desiredTorque );
        }

        that.update = function(){
            that.updateFriction();
            that.updateDrive();
            //that.updateTurn();
        }
        return that;
    }
    tire = tireDef;
})();