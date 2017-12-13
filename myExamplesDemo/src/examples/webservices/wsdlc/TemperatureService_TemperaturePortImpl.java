
package examples.webservices.wsdlc;

import javax.jws.WebService;
import javax.xml.ws.BindingType;


/**
 * 
 *          Returns current temperature in a given U.S. zipcode
 *       
 * 
 * This class was generated by the JAX-WS RI.
 * JAX-WS RI 2.2.11-b150616.1732
 * Generated source version: 2.2
 * 
 */
@WebService(portName = "TemperaturePort", serviceName = "TemperatureService", targetNamespace = "http://www.xmethods.net/sd/TemperatureService.wsdl", wsdlLocation = "/wsdls/TemperatureService.wsdl", endpointInterface = "examples.webservices.wsdlc.TemperaturePortType")
@BindingType("http://schemas.xmlsoap.org/wsdl/soap/http")
public class TemperatureService_TemperaturePortImpl
    implements TemperaturePortType 
{


    public TemperatureService_TemperaturePortImpl() {
    }

    /**
     * 
     * @param parameters
     * @return
     *     returns examples.webservices.wsdlc.GetTempResponse
     */
    public GetTempResponse getTemp(GetTempRequest parameters) { 
        //replace with your impl here
        return null;
    }

}
