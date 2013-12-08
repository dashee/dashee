// Box 2D car definition
(function(){
    // Build a car with our tires
    var carDef = function(world){
        var that = {};
        that.m_tires = [];
        //create car body
        var bodyDef = new b2BodyDef;
        bodyDef.type = b2Body.b2_dynamicBody;
        bodyDef.position.Set(2, 2);
        that.m_body = world.CreateBody(bodyDef);

        var vertices= [];
        vertices[0] =  new b2Vec2(0.2, 0);
        vertices[1] =  new b2Vec2(   0.2, 0.6);
        vertices[2] =  new b2Vec2( -0.2, 0.6);
        vertices[3] =  new b2Vec2(   -0.2,  0);
        //vertices[4] =  new b2Vec2(  -1,  10);
        /*vertices[5] =  new b2Vec2(-2.8, 5.5);
        vertices[6] =  new b2Vec2(  -3, 2.5);
        vertices[7] =  new b2Vec2(-1.5,   0);*/
        var polygonShape = new b2PolygonShape;
        polygonShape.SetAsArray( vertices, 4 );

        var fixDef = new b2FixtureDef;
        fixDef.density = 1.0;
        fixDef.friction = 0.0;
        fixDef.restitution = 0.2;
        fixDef.shape = polygonShape;

        that.m_body.CreateFixture(fixDef);//shape, density*/

        //prepare common joint parameters
        var jointDef = new b2RevoluteJointDef;
        jointDef.bodyA = that.m_body;
        jointDef.enableLimit = true;
        jointDef.lowerAngle = 0;
        jointDef.upperAngle = 0;
        jointDef.localAnchorB.SetZero();//center of tire

        var maxForwardSpeed = 250;
        var maxBackwardSpeed = -40;
        var backTireMaxDriveForce = 300;
        var frontTireMaxDriveForce = 500;
        var backTireMaxLateralImpulse = 8.5;
        var frontTireMaxLateralImpulse = 7.5;

        //back left tire
        var tireLeft = tire(world);
        //tire.setCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
        jointDef.bodyB = tireLeft.m_body;
        jointDef.localAnchorA.Set( -0.2, 0 );
        world.CreateJoint( jointDef );
        that.m_tires.push(tireLeft);

        //back right tire
        var tireRgt = tire(world);
        //tire->setCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
        jointDef.bodyB = tireRgt.m_body;
        jointDef.localAnchorA.Set( 0.2, 0 );
        world.CreateJoint( jointDef );
        that.m_tires.push(tireRgt);

        //front left tire
        var tireFLeft = tire(world);
        //tire->setCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
        jointDef.bodyB = tireFLeft.m_body;
        jointDef.localAnchorA.Set( -0.2, 0.6 );
        var flJoint = world.CreateJoint( jointDef );
        that.m_tires.push(tireFLeft);

        //front right tire
        var tireFRgt = tire(world);
        //tire->setCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
        jointDef.bodyB = tireFRgt.m_body;
        jointDef.localAnchorA.Set( 0.2, 0.6 );
        var frJoint = world.CreateJoint( jointDef );
        that.m_tires.push(tireFRgt);



        that.update = function() {
            for (var i = 0; i < that.m_tires.length; i++)
                that.m_tires[i].update();

            //control steering
            var lockAngle = 35 * DEGTORAD;
            var turnSpeedPerSec = 160 * DEGTORAD;//from lock to lock in 0.5 sec
            var turnPerTimeStep = turnSpeedPerSec / 60.0;
            var desiredAngle = 0;

            if( keys[37] || keys[39]) {
                if(keys[37]){
                    desiredAngle = -lockAngle; 
                }else{
                    desiredAngle = lockAngle; 
                }
            }
            var angleNow = flJoint.GetJointAngle();
            var angleToTurn = desiredAngle - angleNow;
            angleToTurn = b2Math.Clamp( angleToTurn, -turnPerTimeStep, turnPerTimeStep );
            var newAngle = angleNow + angleToTurn;
            flJoint.SetLimits( newAngle, newAngle );
            frJoint.SetLimits( newAngle, newAngle );
        }
        return that;
    }
    car = carDef;
})();